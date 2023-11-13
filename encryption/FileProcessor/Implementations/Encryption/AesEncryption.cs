using System.Security.Cryptography;
using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class AesEncryption : Interfaces.IEncryptionAlgorithm
{
    private readonly byte[] key;
    private readonly byte[] iv;

    public AesEncryption(ISymmetricKeyGenerator keyGenerator)
    {
        key = keyGenerator.GenerateKey();
        iv = keyGenerator.GenerateInitializationVector();
    }

    public byte[] Encrypt(byte[] data)
    {
        using var aes = Aes.Create();
        aes.Key = this.key;
        aes.IV = this.iv;
        using var memoryStream = new MemoryStream();
        using (var cryptoStream = new CryptoStream(memoryStream, aes.CreateEncryptor(), CryptoStreamMode.Write))
        {
            cryptoStream.Write(data, 0, data.Length);
        }
        return memoryStream.ToArray();
    }

    public byte[] Decrypt(byte[] data)
    {
        using var aes = Aes.Create();
        aes.Key = this.key;
        aes.IV = this.iv;
        using var memoryStream = new MemoryStream(data);
        using var cryptoStream = new CryptoStream(memoryStream, aes.CreateDecryptor(), CryptoStreamMode.Read);
        using var resultStream = new MemoryStream();
        cryptoStream.CopyTo(resultStream);
        return resultStream.ToArray();
    }
}