#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <vector>
#include <string>
#include <functional>
#include <unordered_map>

class Arguments {
public:
    Arguments(int argc, char** argv);

    void registerFlag(std::string flag, std::function<void()> predicate);
    void registerFlag(std::string flag, std::function<void(std::string)> predicate);

    const std::vector<std::string>& getAnonymousArgs() const;

    void process();
private:
    const static std::string FLAG_PREFIX;
    const static std::string VERBOSE_FLAG_PREFIX;

    std::vector<std::string> args;
    std::vector<std::string> anonArgs;
    std::unordered_map<std::string, std::function<void()>> noArgFlags;
    std::unordered_map<std::string, std::function<void(std::string)>> oneArgFlags;

    bool isFlag(const std::string& flag) const;
    bool hasFlag(const std::string& flag) const;
    std::string getArg(const std::string& flag) const;
};

#endif
