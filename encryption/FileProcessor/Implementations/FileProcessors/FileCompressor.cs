using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class FileCompressor : Abstract.BaseFileProcessor
{
    private readonly ICompressionAlgorithm compression;

    public FileCompressor(ICompressionAlgorithm compression) : base()
    {
        this.compression = compression;
    }

    protected override byte[] ProcessData(byte[] data)
    {
        return this.compression.Compress(data);
    }
}