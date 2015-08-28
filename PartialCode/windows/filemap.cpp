#include "filemap.h"

FileMap::FileMap()
{
    QMapIterator<int, FileInfo> iter(fileM);
    iter.toFront();
    while(iter.hasNext())
    {
        iter.
        iter.value().initFInfo();
        iter.next();
    }
}


void FileMap::initFileMap()
{
    QMapIterator<int, FileInfo> iter(fileM);
    iter.toFront();
    while(iter.hasNext())
    {
        iter.value().initFInfo();
        iter.next();
    }
}
