
namespace edu.yu.com3640.FileProcessor;

public class Program
{
    public static void Main(string[] args)
    {
        string inputFilePath = args[0]; // path to input file
        string encryptedFile, decryptedFile, zippedFile, unzippedFile;

        var fileEncryptor1 = CreateAESFileEncryptor();
        var fileDecryptor1 = CreateAESFileDecryptor();

        encryptedFile = inputFilePath + ".aes.enc";
        fileEncryptor1.Process(inputFilePath, encryptedFile);

        decryptedFile = inputFilePath + ".aes.dec";
        fileDecryptor1.Process(encryptedFile, decryptedFile);

        var fileEncryptor2 = CreateRSAFileEncryptor();
        var fileDecryptor2 = CreateRSAFileDecryptor();

        encryptedFile = inputFilePath + ".rsa.enc";
        fileEncryptor2.Process(inputFilePath, encryptedFile);

        decryptedFile = inputFilePath + ".rsa.dec";
        fileDecryptor2.Process(encryptedFile, decryptedFile);

        var fileCompressor1 = CreateZipFileCompressor();
        var fileDecompressor1 = CreateZipFileDecompressor();

        zippedFile = inputFilePath + ".zip";
        fileCompressor1.Process(inputFilePath, zippedFile);
        unzippedFile = inputFilePath + "zip.unzipped";
        fileDecompressor1.Process(zippedFile, unzippedFile);

        var fileCompressor2 = CreateGZipFileCompressor();
        var fileDecompressor2 = CreateGZipFileDecompressor();

        zippedFile = inputFilePath + ".gz";
        fileCompressor2.Process(inputFilePath, zippedFile);
        unzippedFile = inputFilePath + "gz.unzipped";
        fileDecompressor2.Process(zippedFile, unzippedFile);
    }


    private static FileProcessor CreateAESFileEncryptor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateAESFileDecryptor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateRSAFileEncryptor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateRSAFileDecryptor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateZipFileCompressor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateZipFileDecompressor()
    {
        throw new NotImplementedException();
    }
       private static FileProcessor CreateGZipFileCompressor()
    {
        throw new NotImplementedException();
    }

    private static FileProcessor CreateGZipFileDecompressor()
    {
        throw new NotImplementedException();
    }

}
