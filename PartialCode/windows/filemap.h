#ifndef FILEMAP_H
#define FILEMAP_H

#include "fileinfo.h"

class FileMap
{
public:
    FileMap();

    void initFileMap();
    QMap<int, FileInfo> fileM;
private:



};

#endif // FILEMAP_H
