using System.Security.Cryptography;
using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class RsaEncryption : Interfaces.IEncryptionAlgorithm
{
    private readonly RSA privateKey;
    private readonly RSA publicKey;

    public RsaEncryption(IAsymmetricKeyGenerator keyGenerator)
    {
        (byte[] publicKey, byte[] privateKey) = keyGenerator.GenerateKeyPair();

        this.publicKey = RSA.Create();
        this.publicKey.ImportRSAPublicKey(publicKey, out _);

        this.privateKey = RSA.Create();
        this.privateKey.ImportRSAPrivateKey(privateKey, out _);
    }

    public byte[] Encrypt(byte[] data)
    {
        return publicKey.Encrypt(data, RSAEncryptionPadding.OaepSHA256);
    }

    public byte[] Decrypt(byte[] data)
    {
        return privateKey.Decrypt(data, RSAEncryptionPadding.OaepSHA256);
    }
}