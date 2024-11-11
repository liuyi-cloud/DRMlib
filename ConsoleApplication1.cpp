// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<mydream.h>
#include <fstream> // 包含文件操作所需的头文件
void saveToFile(const char* filename, CVector<_SAMPLE>& data, size_t size)
{
    // 打开文件，指定为二进制模式
    std::ofstream outFile(filename, std::ios::binary | std::ios::app);
    if (!outFile) {
        std::cerr << "无法打开文件进行写入!" << std::endl;
        return;
    }

    // 写入数据到文件
    outFile.write(reinterpret_cast<char*>(data.data()), size * sizeof(short));

    // 关闭文件
    outFile.close();
   
}




int main()
{
    MyDream mydream;
    string m_outFileName = "temp\\123.dat";
    string filePath = "20240701170045_IQ_FREQ_15760000_BW_20000_FS_40000_CHANNEL_0.iq40";
    string fileName = "datafile\\14.iq40";
    const size_t arraySize = 1024*512;//7647232; // 定义要保存的短整数的数量
    // 创建一个新的 short 数组用于读取数据
    short* readData = new short[arraySize];
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile) {
        std::cerr << "无法打开文件进行读取!" << std::endl;
        return -1;
    }
    inFile.read(reinterpret_cast<char*>(readData), arraySize * sizeof(short));
    std::streamsize bytesRead = inFile.gcount();

    // 如果读取到的字节数为0，说明到达文件末尾
    if (bytesRead == 0) {
        return -1;
    }
    // 计算实际读取的数量，并将其存储到最终数组中
    size_t numShortsRead = bytesRead / sizeof(short);
    mydream.m_bufferin = readData;
    mydream.m_bufferinSize = numShortsRead;
    mydream.m_fileName = "20240701170045_IQ_FREQ_15760000_BW_20000_FS_40000_CHANNEL_0.iq40";
    

    mydream.initDream();//argc, argv
    //mydream.bufferOut;
    FILE* fp2 = fopen("D://test12.dat", "ab");
    int a = fwrite(mydream.bufferOut.data(), sizeof(short), 307200, fp2);
    fclose(fp2);
    
    return 0;
    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
