
#include "sltd.hpp"

using ml::iff::sltd;

sltd::sltd()
{}

sltd::~sltd()
{}

uint32_t sltd::readSLTD(std::istream& input)
{
    uint32_t sltd_size;
    readFormHeader(input, "SLTD", sltd_size);
    
    uint32_t total = read0000(input);

    if (sltd_size != total)
    {
	    std::cout << "FAILED in reading SLTD\n";
	    std::cout << "Possibly a corrupt or non-finished file\n";
	    std::cout << "Read " << total << " out of " << sltd_size << std::endl;
    }

    return total;
}
        
const std::vector<std::string>& sltd::getSlots() const
{
    return slots_;
}

uint32_t sltd::read0000(std::istream& input)
{
    uint32_t size, total;
    std::string form, type;
    
    total = readFormHeader(input, form, size, type);
    
    if(form != "FORM" || type != "0000")
    {
	    std::cout << "Expected FORM: " << form << std::endl;
	    throw std::exception();
    }

    std::string data_header;
    uint32_t data_size, read_size = 0;
    total += readRecordHeader(input, data_header, data_size);
    
    while (read_size < data_size)
    {
        std::string slot_name;
        read_size += read(input, slot_name);

        slots_.push_back(slot_name);
    }

    return total + read_size;
}
