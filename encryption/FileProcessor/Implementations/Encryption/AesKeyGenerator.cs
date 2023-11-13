using System.Security.Cryptography;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class AesKeyGenerator : Interfaces.ISymmetricKeyGenerator
{
    private readonly int keySize;
    private readonly int blockSize;

    public AesKeyGenerator()
    {
        keySize = 256;
        blockSize = 128;
    }

    public AesKeyGenerator(int keySize, int blockSize)
    {
        this.keySize = keySize;
        this.blockSize = blockSize;
    }

    public byte[] GenerateKey()
    {
        using Aes aes = Aes.Create();
        aes.KeySize = keySize;
        aes.GenerateKey();
        return aes.Key;
    }

    public byte[] GenerateInitializationVector()
    {
        using var aes = Aes.Create();
        aes.BlockSize = blockSize;
        aes.GenerateIV();
        return aes.IV;
    }

}

