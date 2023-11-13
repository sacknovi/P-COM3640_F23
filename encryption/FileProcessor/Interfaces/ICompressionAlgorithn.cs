namespace edu.yu.com3640.FileProcessor.Interfaces;

/// <summary>
/// Interface for compression algorithms
/// </summary>
public interface ICompressionAlgorithm
{
    /// <summary>
    /// Compresses the given data
    /// </summary>
    /// <param name="data"></param>
    /// <returns>The compressed data as a byte array</returns>
    byte[] Compress(byte[] data);

    /// <summary>
    /// Decompresses the given data
    /// <param name="data"></param>
    /// <returns>The decompressed data as a byte array</returns>
    byte[] Decompress(byte[] data);
}
