#include "Arguments.hpp"
#include <iostream>
#include <algorithm>

// static
const std::string Arguments::FLAG_PREFIX = "-";
// static
const std::string Arguments::VERBOSE_FLAG_PREFIX = "--";

Arguments::Arguments(int argc, char** argv)
    : good(true) {
    args.resize(argc);
    for(int i = 0; i < argc; i++) {
        args[i] = argv[i];
    }
}

void Arguments::registerFlag(std::string flag, std::function<void()> predicate) {
    noArgFlags[flag] = predicate;
}

void Arguments::registerFlag(std::string flag, std::function<void(std::string)> predicate) {
    oneArgFlags[flag] = predicate;
}

const std::vector<std::string>& Arguments::getAnonymousArgs() const {
    return anonArgs;
}

void Arguments::process() {
    for(auto it = args.begin(); it != args.end() && good; ++it) {
        if(isFlag(*it)) {
            if(noArgFlags.find(*it) != noArgFlags.end()) {
                noArgFlags[*it]();
            } else if(oneArgFlags.find(*it) != oneArgFlags.end()) {
                auto arg = getArg(*it);
                if(arg != "") {
                    oneArgFlags[*it](arg);
                    ++it;
                }
            } else {
                std::cerr << "Unknown flag " << *it << std::endl;
                good = false;
            }
        } else if(it != args.begin()) {
            anonArgs.push_back(*it);
        }
    }
}

bool Arguments::fail() const {
    return !good;
}

bool Arguments::isFlag(const std::string& flag) const {
    bool verbose = flag.compare(0, VERBOSE_FLAG_PREFIX.length(), VERBOSE_FLAG_PREFIX) == 0;
    bool normal = flag.compare(0, FLAG_PREFIX.length(), FLAG_PREFIX) == 0;

    return verbose || normal;
}

bool Arguments::hasFlag(const std::string& flag) const {
    return std::find(args.begin(), args.end(), flag) != args.end();
}

std::string Arguments::getArg(const std::string& flag) {
    auto it = std::find(args.begin(), args.end(), flag);
    if(it == args.end()) {
        std::cerr << "Unknown flag " << flag << std::endl;
        good = false;
        return "";
    }

    ++it;
    if(it == args.end()) {
        std::cerr << "Flag " << flag << " does not have an argument" << std::endl;
        good = false;
        return "";
    }

    if(isFlag(*it)) {
        std::cerr << "Flag " << flag << " cannot take flag " << *it << " as an argument" << std::endl;
        good = false;
        return "";
    }

    return *it;
}
