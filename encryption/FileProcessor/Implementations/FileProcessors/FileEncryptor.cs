using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class FileEncryptor : Abstract.BaseFileProcessor
{
    private readonly IEncryptionAlgorithm encryption;

    public FileEncryptor(IEncryptionAlgorithm encryption) : base() => this.encryption = encryption;

    protected override byte[] ProcessData(byte[] data)
    {
        return this.encryption.Encrypt(data);
    }
}   