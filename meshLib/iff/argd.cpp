
#include "argd.hpp"

using ml::iff::argd;

argd::argd()
{}

argd::~argd()
{}

uint32_t argd::readARGD(std::istream& input)
{
    uint32_t argd_size;
    readFormHeader(input, "ARGD", argd_size);
    
    uint32_t total = read0000(input);

    if (argd_size != total)
    {
	    std::cout << "FAILED in reading ARGD\n";
	    std::cout << "Possibly a corrupt or non-finished file\n";
	    std::cout << "Read " << total << " out of " << argd_size << std::endl;
    }

    return total;
}

uint32_t argd::read0000(std::istream& input)
{
    uint32_t size, total, read_size = 0;
    std::string form, type;
    
    total = readFormHeader(input, form, size, type);
    
    if(form != "FORM" || type != "0000")
    {
	    std::cout << "Expected FORM: " << form << std::endl;
	    throw std::exception();
    }


    while (read_size < size)
    {
        std::string arg_header;
        uint32_t arg_size, arg_read_size = 0;
        read_size += readRecordHeader(input, arg_header, arg_size);

        std::vector<std::string> slots;
        while (arg_read_size < arg_size)
        {
            std::string slot_name;
            arg_read_size += read(input, slot_name);

            slots.push_back(slot_name);
        }

        read_size += arg_read_size;
        slot_arrangements_.push_back(std::move(slots));
    }

    return total += read_size;
}
