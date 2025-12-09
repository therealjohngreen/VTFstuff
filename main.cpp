// and now its gone

#include <iostream>
#include <unordered_map> 
#include <iomanip> // for std::setw and std::hex
#include <unordered_set>

// some shit

#include <filesystem>
#include <string>

#include "VTFLib.h"

namespace fs = std::filesystem;

// if you wanna see the image data
// dataSize is the length of the array lpImageData
void printImageData(vlByte* lpImageData, size_t dataSize) {
    for (size_t i = 0; i < dataSize; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(lpImageData[i]) << " ";
        if ((i + 1) % 16 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::dec << std::endl;
}

// dont use this function
bool isThisOpaque(VTFLib::CVTFFile& vtf, const vlChar* filePath, const VTFImageFormat& format)
{
    if (!vtf.Load(filePath, false)) {
        std::cerr << "failed to load vtf: " << filePath << std::endl;
        std::cerr << vlGetLastError() << std::endl;
        return false;
    }

    vlUInt uiWidth = vtf.GetWidth();
    vlUInt uiHeight = vtf.GetHeight();
    vlByte* lpImageData = new vlByte[vtf.ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

    if (!VTFLib::CVTFFile::ConvertToRGBA8888(vtf.GetData(0, 0, 0, 0), lpImageData, uiWidth, uiHeight, format)) {
        std::cerr << "failed to convert to RGBA888: " << filePath << std::endl;
        std::cerr << vlGetLastError() << std::endl;
        return false;
    }

    for (vlUInt y = 0; y < uiHeight; ++y) {
        for (vlUInt x = 0; x < uiWidth; ++x) {
            vlUInt index = (y * uiWidth + x) * 4;
            int alpha = lpImageData[index + 3]; // ignore this error

            if (alpha < 254) {
                delete[] lpImageData;
                return false;
            }
        }
    }

    delete[] lpImageData;
    return true;
}

// copy specific files
/* arguments:
* formatFilter: whitelist of VTFImageFormat in an unordered_set, leave empty to allow all file format
* checkIfOpaque: only copy if the alpha channel is opaque, off by default
*/
void CopySpecificFiles(const fs::path& input, const fs::path& output, const std::unordered_set<VTFImageFormat>& formatFilter, const bool& checkIfOpaque = false)
{
    try {
        for (const auto& entry : fs::recursive_directory_iterator(input)) {
            if (entry.is_regular_file() && entry.path().extension() == ".vtf") {
                const fs::path& relativePath = fs::relative(entry.path(), input);
                fs::path destinationPath = output / relativePath;

                VTFLib::CVTFFile vtf;

                if (!vtf.Load(entry.path().string().c_str(), true)) {
                    std::cerr << "failed to load vtf: " << entry.path().string().c_str() << std::endl; // dangling pointers
                    std::cerr << vlGetLastError() << std::endl;
                    return;
                }

                VTFImageFormat format = vtf.GetFormat();

                if (!formatFilter.empty() && !(formatFilter.find(format) != formatFilter.end())) {
                    continue;
                }

                bool isOpaque = true;

                if (checkIfOpaque) {
                    isOpaque = isThisOpaque(vtf, entry.path().string().c_str(), format);
                }

                if (isOpaque) {
                    fs::create_directories(destinationPath.parent_path());
                    fs::copy_file(entry.path(), destinationPath, fs::copy_options::overwrite_existing);
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// prints the number of files for each image format
void PrintNumOfEachFormat(const fs::path& input) {
    std::unordered_map<VTFImageFormat, int> umap;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(input)) {
            if (entry.is_regular_file() && entry.path().extension() == ".vtf") {
                VTFLib::CVTFFile vtf;
                if (!vtf.Load(entry.path().string().c_str(), true)) {
                    std::cerr << "failed to load vtf: " << entry.path().string().c_str() << std::endl; // dangling pointers
                    std::cerr << vlGetLastError() << std::endl;
                    return;
                }

                VTFImageFormat format = vtf.GetFormat();
                if (umap.find(format) != umap.end()) {
                    umap[format]++;
                } else {
                    umap[format] = 1;
                }
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl << std::setw(10) << "format" << std::setw(7) << "bpp" << std::setw(9) << "amount" << std::endl << std::endl;

    for (auto& format : umap) {
        SVTFImageFormatInfo formatInfo = VTFLib::CVTFFile::GetImageFormatInfo(format.first);
        std::cout << std::setw(10) << formatInfo.lpName << std::setw(7) << formatInfo.uiBitsPerPixel << std::setw(9) << format.second << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    std::cout << "balls" << std::endl;

    fs::path inputPath("INPUT FOLDER PATH HERE");
    fs::path outputPath("OUTPUT FOLDER PATH HERE");

    if (!fs::exists(inputPath)) {
        std::cerr << "Input folder does not exist" << std::endl;
        return 1;
    }

    // exemple of filter for formats
    // leave empty to allow all file format
    // find all formats here https://www.wunderboy.org/docs/vtflib_docs/_v_t_f_format_8h.html#4dd5b0e93db484e217b78759c3fe568f
    /*std::unordered_set<VTFImageFormat> formatFilter = {
        IMAGE_FORMAT_RGBA8888,
        IMAGE_FORMAT_DXT5,
        IMAGE_FORMAT_RGB888,
        IMAGE_FORMAT_BGR888
    };*/

    //CopySpecificFiles(inputPath, outputPath, formatFilter); // add 4th argument (true) to only copy those with opaque alpha channel

    //PrintNumOfEachFormat(inputPath);

    std::cout << "========================================" << std::endl;
    std::cout << "OVEROVEROVEROVEROVEROVEROVEROVEROVEROVER" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}