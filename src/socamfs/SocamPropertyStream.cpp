#include <socamfs/SocamPropertyStream.h>

namespace SOCAM {

//PROPERTY CLASS
//--------------

Property::Property() {

}

Property::Property(string name_p, string value_p, P_TYPE type_p) {
    this->name = name_p;
    this->value = value_p;
    this->type=type_p;
}

Property::Property(const Property &p) {
    this->name = p.name;
    this->value = p.value;
    this->type = p.type;
}

Property::~Property() {

}

string Property::getName() {
    return this->name;
}

string Property::getValue() {
    return this->value;
}

void Property::setValue(string value) {
    this->value = string(value);
}


P_TYPE Property::getType() {
    return this->type;
}

void Property::toStream(ostream & out) {
    out<<this->name<<" = "<<this->value<<endl;
}

string Property::toString() {
    return (this->name+" = "+this->value+"\r\n");
}



//SocamPropertyStream
//-----------------
/** Default constructor */
SocamPropertyStream::SocamPropertyStream(string path) : ifstream(path.c_str(), ios::in){
    if (!this->is_open()) {
        this->status=P_NOT_OPEN;
        this->already=false;
        LOG_ERROR("SocamPropertyStream::constructor >> BASE IFSTREAM NOT OPEN ERROR!!")
        return;
    }
        
    this->status=P_NO_ERROR;
    this->already=true;
    
    this->init(path);
}


/** Default destructor */
SocamPropertyStream::~SocamPropertyStream() {
    std::map<std::string, Property*>::iterator it = entries.begin();
    for (; it != this->entries.end(); it++) {
            delete it->second;
    }
    this->entries.clear();
}

bool SocamPropertyStream::isAlready() {
    return (this->already && this->eof() && this->is_open());
}

bool SocamPropertyStream::isEmpty() {
    return this->entries.empty();
}

P_RESULT SocamPropertyStream::Status() {
    return this->status;
}

string SocamPropertyStream::getValue(string name) {
    Property* prop = entries[name];
    if(prop!=NULL) {
	return prop->getValue();
    } else {
        return "";
    }
}

void SocamPropertyStream::setValue(string name, string value, int type) {
    LOG_INFO("SocamPropertyStream::setValue[" << name << "]=" << value)
    Property* p = entries[name];
    if(p == NULL) {
        p = new Property(name, value, type);
	entries.insert(std::pair<std::string, Property*>(name, p));
    } else {
        p->setValue(value);
    }
    LOG_INFO("SocamPropertyStream::value set[" << name << "]=" << value)
}

void SocamPropertyStream::setValue(string name, string value) {
    this->setValue(name,value,P_STRING);
}

void SocamPropertyStream::toStream(ostream & out) {
    if (!this->isEmpty()) {
	std::map<std::string, Property*>::iterator it = entries.begin();
        for (; it != this->entries.end(); it++) {
            it->second->toStream(out);
        }
    }
}

string SocamPropertyStream::toString() {
    string str="";
    if (!this->isEmpty()) {
        std::map<std::string, Property*>::iterator it = entries.begin();
        for (; it != this->entries.end(); it++) {
            str += it->second->toString();
        }
    }
    return str;
}

void SocamPropertyStream::init(string path) {
    if (!this->is_open()) {
        LOG_ERROR("SocamPropertyStream::init >> Base ifstream NOT OPEN ERROR!! (Maybe invalid path..)")
        this->status=P_NOT_OPEN;
        already=false;
        return;
    }

    try {
        char * buffer=new char[MAX_SIZE_LINE]; 
       
        while (!this->eof()) {
            init_buffer(buffer,MAX_SIZE_LINE);
            this->getline(buffer,MAX_SIZE_LINE, '\n');
            string line(buffer);
            
            if (line.empty() || line.size()>MAX_SIZE_LINE || line[0]=='#' || line[0]==' ')
                continue;
            
            LOG_DEBUG("Scanning line ["<<line<<"]..")
            std::vector<std::string> strs;
           
              const char* p;

              for (p = strtok( (char*)line.c_str(), " " );  p; )
              {
                string str = p;
                strs.push_back(str);
		p=strtok(NULL," ");
              }
            
            
            if(!strs.empty() && strs.size()==3) {
                Property *p = new Property(strs[0],strs[2],P_STRING);
                entries.insert(std::pair<std::string, Property*>(strs[0], p));
                LOG_INFO("Property[" << strs[0] << "]=" << strs[2])
            }
            else {
                //not compute this line of property file
                LOG_WARN("SocamPropertyStream::init >> Invalid line property!.. Skipping!")
            }
        }
        
        LOG_INFO("SocamPropertyStream::init >> initialized")
        
        delete [] buffer;
        if (isEmpty())  status=P_EMPTY_FILE;
        else            status=P_NO_ERROR;
        already=true;
        
        close();
        
    }
    catch (std::exception & ex) {
        this->status=P_IO_ERROR;
        already=false;
        LOG_ERROR("SocamPropertyStream::init() >> ERROR: "<<ex.what())
        throw SocamException("Error while reading property file!",ex.what(),(int)this->status,"SocamPropertyStream::init()");
    }

}


void SocamPropertyStream::save(string path) {
    
    
    LOG_INFO("SocamPropertyStream::save >> path=" << path)
                
    open(path.c_str());
    
    ostringstream tempFileContent;

    try {

        //Copy current settings
        list<string> settings;
	std::map<std::string, Property*> entriesCopy = std::map<std::string, Property*>(entries);

        char * buffer=new char[MAX_SIZE_LINE]; 
       
        while (!this->eof()) {
            init_buffer(buffer,MAX_SIZE_LINE);
            this->getline(buffer,MAX_SIZE_LINE, '\n');
            string line(buffer);
            
            if (line.empty() || line.size()>MAX_SIZE_LINE || line[0]=='#' || line[0]==' ') {
                LOG_INFO("SocamPropertyStream::save >> copy line")
                tempFileContent << line << endl;
                continue;
            }
            
            LOG_DEBUG("Scanning line ["<<line<<"]..")
            std::vector<std::string> strs;
           
            const char* p;

            for (p = strtok( (char*)line.c_str(), " " );  p; ) {
                string str = p;
                strs.push_back(str);
		p=strtok(NULL," ");
            }
            
            if(!strs.empty() && strs.size()==3) {
                Property *property = entries[strs[0]];
                if(property->getValue().size()>0) {
                    LOG_INFO("SocamPropertyStream::save >> property[" << strs[0] << "]=" << property->getValue())
                    tempFileContent << strs[0] << " = " << property->getValue() << endl;
                    entriesCopy.erase(strs[0]);
                } else {
                    LOG_INFO("SocamPropertyStream::save >> copy line (2)")
                    tempFileContent << line << endl;
                }
            }
            else {
                //not compute this line of property file
                LOG_INFO("SocamPropertyStream::save >> copy line (3)")
                tempFileContent << line << endl;
                
            }
        }

	//Save remaining settings in map
	map<string, Property*>::iterator it;

        for (it = entriesCopy.begin(); it != entriesCopy.end(); it++) {
            pair<string,Property*> entry = *it;
            Property *p = entry.second;
            tempFileContent << p->getName() << " = " << p->getValue() << endl;
        }
        
        close();
        
        ofstream settingsFile(path.c_str());
        settingsFile << tempFileContent.str()<<endl;
        settingsFile.close();
        
        
        LOG_INFO("SocamPropertyStream::save >>saved")
        
        delete [] buffer;
        if (isEmpty())  status=P_EMPTY_FILE;
        else            status=P_NO_ERROR;
        already=true;
    }
    catch (std::exception & ex) {
        this->status=P_IO_ERROR;
        already=false;
        LOG_ERROR("SocamPropertyStream::init() >> ERROR: "<<ex.what())
        throw SocamException("Error while reading property file!",ex.what(),(int)this->status,"SocamPropertyStream::init()");
    }

}




void SocamPropertyStream::init_buffer(char * buffer, size_t size) {
     for (int i=0;i<size;i++)
         buffer[i]='\0';
}

 
}
