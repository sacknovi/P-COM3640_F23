using System.IO.Compression;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class GZipCompression : Interfaces.ICompressionAlgorithm
{
    public byte[] Compress(byte[] data)
    {
        using var memoryStream = new MemoryStream();
        using (var gzipStream = new GZipStream(memoryStream, CompressionMode.Compress, true))
        {
            gzipStream.Write(data, 0, data.Length);
        }
        return memoryStream.ToArray();
    }

    public byte[] Decompress(byte[] data)
    {
        using var memoryStream = new MemoryStream(data);
        using var gzipStream = new GZipStream(memoryStream, CompressionMode.Decompress);
        using var resultStream = new MemoryStream();
        gzipStream.CopyTo(resultStream);
        return resultStream.ToArray();
    }
}
