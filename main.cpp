#include "tomlgen.h"
#include <fstream>

int main()
{
    toml::TomlRoot tomlroot;

    toml::TomlTable comm("serial");

    toml::TomlElement port(toml::TomlKey("port"),toml::TomlValue("/dev/ttyS0",1));

    toml::TomlElement baud(toml::TomlKey("baud"),toml::TomlValue(9600));

    toml::TomlElement databits(toml::TomlKey("data_bits"),toml::TomlValue(8));

    comm.addElement(port);
    comm.addElement(baud);
    comm.addElement(databits);

    tomlroot.addTable(comm);


    toml::TomlTable ether("ethernet");
    toml::TomlElement ipaddr(toml::TomlKey("ip_address"),toml::TomlValue("192.168.1.12",1));
    toml::TomlElement subnetmask(toml::TomlKey("subnet_mask"),toml::TomlValue("255.255.255.0",1));
    toml::TomlElement defaultgateway(toml::TomlKey("default_gateway"),toml::TomlValue("192.168.1.1",1));

    ether.addElement(ipaddr);
    ether.addElement(subnetmask);
    ether.addElement(defaultgateway);

    tomlroot.addTable(ether);

    std::string tomlconf=tomlroot.toString();
    std::cout<<tomlconf;

    std::ofstream fs;
    fs.open("/home/lokesaheb/testfile.toml",std::ios::ate);

    fs.write(tomlconf.c_str(),tomlconf.length());

    fs.close();

    return 0;
}
