#ifndef MNISTLOADER_H
#define MNISTLOADER_H

#include <string>
#include <inttypes.h>

class MnistLoader
{
public:
    MnistLoader();

    void load(const std::string &databaseFileName, const std::string &labelsFileName);

private:
    void loadDatabase(const std::string &fileName);
    void loadLabels(const std::string &fileName);

    static int8_t readInt8(std::ifstream &file);
    static int32_t readInt32(std::ifstream &file);
};

#endif // MNISTLOADER_H
