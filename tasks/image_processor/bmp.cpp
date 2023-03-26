#include "bmp.h" 

BMP::BMP(const std::string& filename) {
    Read(filename);
}

void BMP::Read(const std::string& filename) {
    std::ifstream in(filename, std::ios_base::binary);
    if (!in.good()) {
        throw std::runtime_error("Input file does not exists or is unaccesible!");
    } 
    in.read(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    if (bmp_header.file_type != 0x4D42) { // little endian
        throw std::runtime_error("Wrong format of input file!");
    }
    in.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
    
    std::cerr << dib_header.size << "!!!!!!!!\n";
    
    if (dib_header.width < 0 || dib_header.height < 0) {
        throw std::runtime_error("Wrong format of input file!");
    }

    pixel_array.resize(dib_header.height);
    for (auto &u: pixel_array) {
        u.resize(dib_header.width);
    }

    if (dib_header.width % 4 == 0) {
        for (auto &u: pixel_array) {
            in.read(reinterpret_cast<char*>(u.data()), dib_header.width * 3);
        }
    } else {
        uint32_t row_size = (24 * dib_header.width) / 8;
        uint32_t padding_size = 0;
        while ((row_size + padding_size) % 4 != 0) {
            ++padding_size;
        }
        std::vector <uint8_t> trash(padding_size);  

        for (int32_t i = 0; i < dib_header.height; ++i) {
            in.read((char*)(pixel_array[i].data()), row_size);
            in.read((char*)(trash.data()), trash.size());
        }
    }
}

void BMP::Write(const std::string& filename) {
    std::ofstream out(filename, std::ios_base::binary);
    std::cerr << filename << "\n";
    if (!out.good()) {
        throw std::runtime_error("Output file directory is unaccesible!");
    }
    
    out.write(reinterpret_cast<char*>(&bmp_header), sizeof(bmp_header));
    out.write(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));
    
    if (dib_header.width % 4 == 0) {
        for (auto &u: pixel_array) {
            out.write(reinterpret_cast<char*>(u.data()), dib_header.width * 3);
        }
    } else {
        uint32_t row_size = (24 * dib_header.width) / 8;
        uint32_t padding_size = 0;
        while ((row_size + padding_size) % 4 != 0) {
            ++padding_size;
        }
        std::vector <uint8_t> trash(padding_size);

        for (int i = 0; i < dib_header.height; ++i) {
            out.write(reinterpret_cast<char*>(pixel_array[i].data()), row_size);
            out.write(reinterpret_cast<char*>(trash.data()), trash.size());
        }
    }
    out.close();
} 

void BMP::ApplyFilter(const Filter& fl) {
    if (fl.FilterName() == "CropFilter") {
        fl.ApplyFilter(pixel_array);
        fl.ChangeSize(dib_header.height, dib_header.width);
        return;
    }
    std::cerr << fl.FilterName() << "\n";
    std::cerr << static_cast<int32_t>(this->pixel_array[1][1].R) << "!\n";
    fl.ApplyFilter(this->pixel_array);
}