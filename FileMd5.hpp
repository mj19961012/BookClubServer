//
// Created by MJ on 2018/6/15.
//

#ifndef __CFS_SERVER_FILE_MD5_HPP_
#define __CFS_SERVER_FILE_MD5_HPP_

#include <string>

/* typedef a 32 bit type */
typedef unsigned long int UINT4;

/* Data structure for MD5 (Message Digest) computation */
typedef struct {
    UINT4 i[2];                   /* number of _bits_ handled mod 2^64 */
    UINT4 buf[4];                                    /* scratch buffer */
    unsigned char in[64];                              /* input buffer */
    unsigned char digest[16];     /* actual digest after MD5Final call */
} MD5_CTX;

class FileMd5
{
public:
    static FileMd5 * getInstance()
    {
        if(nullptr == instance)
        {
            instance = new FileMd5;
        }
        return instance;
    }

    void MD5Init(MD5_CTX *mdContext);
    void MD5Update(MD5_CTX *mdContext, unsigned char *inBuf, unsigned int inLen);
    void MD5Final(MD5_CTX *mdContext);
    static void Transform(UINT4 *buf, UINT4 *in);
    std::string MD5_file(const char *path, int md5_len = 32);

private:
    static  FileMd5 * instance;
};


#endif//__CFS_SERVER_FILE_MD5_HPP_
