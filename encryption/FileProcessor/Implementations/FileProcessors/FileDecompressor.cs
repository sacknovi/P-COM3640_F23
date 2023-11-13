using edu.yu.com3640.FileProcessor.Interfaces;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class FileDecompressor : Abstract.BaseFileProcessor
{
    private readonly ICompressionAlgorithm compression;

    public FileDecompressor(ICompressionAlgorithm compression) : base()
    {
        this.compression = compression;
    }

    protected override byte[] ProcessData(byte[] data)
    {
        return this.compression.Decompress(data);
    }
}