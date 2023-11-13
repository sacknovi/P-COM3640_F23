using System.IO.Compression;

namespace edu.yu.com3640.FileProcessor.Implementations;

public class ZipCompression : Interfaces.ICompressionAlgorithm
{
    public byte[] Compress(byte[] data)
    {
        using var memoryStream = new MemoryStream();
        using (var zipArchive = new ZipArchive(memoryStream, ZipArchiveMode.Create, true))
        {
            var zipEntry = zipArchive.CreateEntry("data");
            using var zipEntryStream = zipEntry.Open();
            zipEntryStream.Write(data, 0, data.Length);
        }
        return memoryStream.ToArray();
    }

    public byte[] Decompress(byte[] data)
    {
        using var memoryStream = new MemoryStream(data);
        using var zipArchive = new ZipArchive(memoryStream, ZipArchiveMode.Read);
        var zipEntry = zipArchive.Entries[0];
        using var zipEntryStream = zipEntry.Open();
        using var resultStream = new MemoryStream();
        zipEntryStream.CopyTo(resultStream);
        return resultStream.ToArray();
    }
}
