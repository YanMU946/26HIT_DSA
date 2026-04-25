#include "huffman.h"

int main()
{
    int ascii_buf[129];
    ifstream input_msg("input.in");
    if (!input_msg.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    string str((istreambuf_iterator<char>(input_msg)), istreambuf_iterator<char>());
    cout << str << endl;
    input_msg.close();

    huffman<char> hf(str);
    hf.getcode();

    ofstream encode_msg("encode.bin");
    if (!encode_msg.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    encode_msg << hf.encode(str);
    encode_msg.close();

    hf.get_compress_rate("input.in", "encode.bin");

    ofstream decode_msg("decode.out");
    if (!decode_msg.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    decode_msg << hf.decode(hf.encode(str));
    decode_msg.close();
    return 0;
}
