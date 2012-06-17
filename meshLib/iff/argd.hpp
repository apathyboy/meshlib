
#ifndef MESHLIB_IFF_ARGD_H_
#define MESHLIB_IFF_ARGD_H_

#include <cstdint>
#include <string>
#include <vector>

#include "meshLib/base.hpp"

namespace ml {
namespace iff {

    class argd : public base
    {
    public:
        argd();
        ~argd();

        uint32_t readARGD(std::istream& input);

        const std::vector<std::vector<std::string>>& getSlotArrangements() const;

    private:
        uint32_t read0000(std::istream& input);

        std::vector<std::vector<std::string>> slot_arrangements_;
    };

}}

#endif  // MESHLIB_IFF_ARGD_H_
