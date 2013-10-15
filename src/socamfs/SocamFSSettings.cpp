#include <socamfs/SocamFSSettings.h>

SocamFSSettings::SocamFSSettings() {
    LOG_INFO("Initializing socamfs settinfs from ["<<SOCAM_CONF<<"]..")
    properties = new SocamPropertyStream(SOCAM_CONF);
    LOG_INFO("Initialized OK")
}

SocamFSSettings::~SocamFSSettings() {
    if(properties != NULL) {
        delete properties;
    }
}

string SocamFSSettings::getValue(string name) {
    cout << "SocamFSSettings::getValue(" << name << ")" << endl;
    return properties->getValue(name);
}

void SocamFSSettings::setValue(string name, string value) {
    LOG_INFO("SocamFSSettings::setValue[" << name << "]=" << value)
    properties->setValue(name, value);
}

void SocamFSSettings::save() {
    properties->save(SOCAM_CONF);
}
