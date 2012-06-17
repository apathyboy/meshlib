
#ifndef MESHLIB_IFF_SLTD_H_
#define MESHLIB_IFF_SLTD_H_

#include <cstdint>
#include <string>
#include <vector>

#include "meshLib/base.hpp"

namespace ml {
namespace iff {

    class sltd : public base
    {
    public:
        sltd();
        ~sltd();

        uint32_t readSLTD(std::istream& input);

        const std::vector<std::string>& getSlots() const;

    private:
        uint32_t read0000(std::istream& input);

        std::vector<std::string> slots_;
    };

}}

#endif  // MESHLIB_IFF_SLTD_H_
