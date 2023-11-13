using System.Security.Cryptography;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class RsaKeyGenerator : Interfaces.IAsymmetricKeyGenerator
{
    private readonly int keySize;

    public RsaKeyGenerator() => keySize = 2048;

    public RsaKeyGenerator(int keySize) => this.keySize = keySize;

    public (byte[] publicKey, byte[] privateKey) GenerateKeyPair()
    {
        using RSA rsa = RSA.Create();
        rsa.KeySize = keySize;
        return (rsa.ExportRSAPublicKey(), rsa.ExportRSAPrivateKey());
    }
}
