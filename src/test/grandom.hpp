//
// Created by Gabriele Santi on 07/10/16.
//

#ifndef ALGOWEB_GRANDOM_HPP
#define ALGOWEB_GRANDOM_HPP

#include <vector>

#include "../utilities/optionparser.h"
#include "../FileIO/GraphIO.hpp"
#include "../Grandom/GraphGen.hpp"
#include "../AlgoWEB.hpp"

extern bool __VERB;

struct Arg : public option::Arg {
    static void printError(const char *msg1, const option::Option &opt, const char *msg2) {
        std::cerr << msg1 << opt.name << msg2;
    }

    static option::ArgStatus Unknown(const option::Option &option, bool msg) {
        if (msg)
            printError("Unknown option '", option, "'\n");

        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Required(const option::Option &option, bool msg) {
        if (option.arg != 0)
            return option::ARG_OK;

        if (msg) printError("Option '", option, "' requires an argument\n");
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus String(const option::Option &option, bool msg) {
        if (option.arg != 0 && option.arg[0] != 0)
            return option::ARG_OK;

        if (msg) printError("Option '", option, "' requires a non-empty argument\n");
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Numeric(const option::Option &option, bool msg) {
        std::string::size_type *pt = nullptr;

        if (option.arg != 0 && std::stoul(option.arg, pt, 10)) {};
        if (pt != (unsigned long *) option.arg)
            return option::ARG_OK;

        if (msg)
            printError("Option '", option, "' requires a numeric argument\n");

        return option::ARG_ILLEGAL;
    }
};

enum OptionIndex {
    UNKNOWN,
    VERTICES,
    EDGES,
    MAX_WEIGHT,
    TARGET_DIR,
    SEED,
    VERBOSE,
    HELP
};

const option::Descriptor usage[] = {
        {UNKNOWN,    0, "",  "",           Arg::Unknown, "USAGE: grandom [options]\n\n"
                                                                 "Options:"},
        {VERTICES,   0, "n", "vertices",   Arg::Numeric, "  -n <num>, \t--vertices=<num>  \tCompulsory argument; number of vertices."},
        {EDGES,      0, "m", "edges",      Arg::Numeric, "  -m <num>, \t--edges=<num>  \tCompulsory argument; number of edges."},
        {MAX_WEIGHT, 0, "w", "max-weight", Arg::Numeric, "  -w <num>, \t--max-weight=<num>  \tCompulsory argument; maximum integer weight for the edges."},
        {TARGET_DIR, 0, "d", "target-dir", Arg::String,  "  -d <path>, \t--target-dir=<path>  \tDefault value is \"./\"; where to save the .cwg file."
                                                                 "A correct string is formed by path+filename, e.g. /path/to/dir/graph"},
        {SEED,       0, "s", "seed",       Arg::Numeric, "  -s <num>, \t--seed=<num> \tIf specified, the seed to the random generator (Mersenne Twister);"
                                                                 " otherwise, wall clock is taken into account."},
        {VERBOSE,    0, "v", "verbose",    Arg::None,    "  -v, \t--verbose \tVerbose output."},
        {HELP,       0, "h", "help",       Arg::None,    "  -h, \t--help  \tPrint usage and exit."},
        {UNKNOWN,    0, "",  "",           Arg::None,
                                                         "\nExamples:\n"
                                                                 "  grandom -n 20 -m 36 -w 100 -d=/home/test/rand_graph -v\n"
                                                                 "  grandom --vertices=20 --edges=36 --max-weight=100 --verbose\n"
                                                                 "  grandom -h \n"},
        {0,          0, 0,   0,            0,            0}
};

#endif //ALGOWEB_GRANDOM_HPP
