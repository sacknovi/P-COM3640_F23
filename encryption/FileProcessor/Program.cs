
using edu.yu.com3640.FileProcessor.Abstract;
using edu.yu.com3640.FileProcessor.Implementations;
using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor;

public class Program
{
    public static void Main(string[] args)
    {
        string inputFilePath = args[0]; // path to input file

        BaseFileProcessor fileProcessor;
        IEncryptionAlgorithm encryption;
        ICompressionAlgorithm compression;
        string encryptedFile, decryptedFile, zippedFile, unzippedFile;

        // AES Encryption and Decryption
        // ...............................................
        encryption = new AesEncryption(new AesKeyGenerator());

        fileProcessor = new FileEncryptor(encryption);
        encryptedFile = inputFilePath + ".aes.enc";
        fileProcessor.Process(inputFilePath, encryptedFile);

        fileProcessor = new FileDecryptor(encryption);
        decryptedFile = inputFilePath + ".aes.dec";
        fileProcessor.Process(encryptedFile, decryptedFile);

        // RSA Encryption and Decryption
        // ...............................................
        encryption = new RsaEncryption(new RsaKeyGenerator());

        fileProcessor = new FileEncryptor(encryption);
        encryptedFile = inputFilePath + ".rsa.enc";
        fileProcessor.Process(inputFilePath, encryptedFile);

        fileProcessor = new FileDecryptor(encryption);
        decryptedFile = inputFilePath + ".rsa.dec";
        fileProcessor.Process(encryptedFile, decryptedFile);

        // Zip and Unzip
        // ...............................................
        compression = new ZipCompression();

        fileProcessor = new FileCompressor(compression);
        zippedFile = inputFilePath + ".zip";
        fileProcessor.Process(inputFilePath, zippedFile);

        fileProcessor = new FileDecompressor(compression);
        unzippedFile = inputFilePath + ".zip.unzipped";
        fileProcessor.Process(zippedFile, unzippedFile);

        // GZip and UnGzip
        // ...............................................
        compression = new GZipCompression();

        fileProcessor = new FileCompressor(compression);
        zippedFile = inputFilePath + ".gz";
        fileProcessor.Process(inputFilePath, zippedFile);

        fileProcessor = new FileDecompressor(compression);
        unzippedFile = inputFilePath + ".gz.unzipped";
        fileProcessor.Process(zippedFile, unzippedFile);
    }

}
