namespace edu.yu.com3640.FileProcessor.Interfaces;

public interface IAsymmetricKeyGenerator
{
    /// <summary>
    /// Generates a key pair for asymmetric encryption algorithms
    /// </summary>
    /// <returns>The public and private keys</returns>
    (byte[] publicKey, byte[] privateKey) GenerateKeyPair();
}
