#pragma once

class Pipeline final
{
public:
    Pipeline() = delete;
    Pipeline(const char* vertFilename, const char* fragFilename);
    ~Pipeline();
    Pipeline(const Pipeline& rhs) = delete;
    Pipeline& operator=(const Pipeline& rhs) = delete;

private:
    static std::vector<char> readFile(const char* filename);
};

