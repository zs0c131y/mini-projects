import java.io.FileInputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class HashingTool {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("1. Hash a string");
        System.out.println("2. Hash a file");
        System.out.print("Enter your choice: ");
        int choice = scanner.nextInt();
        scanner.nextLine(); // consume newline

        switch (choice) {
            case 1:
                System.out.print("Enter the string to hash: ");
                String inputString = scanner.nextLine();
                hashString(inputString);
                break;
            case 2:
                System.out.print("Enter the filename to hash: ");
                String filename = scanner.nextLine();
                try {
                    hashFile(filename);
                } catch (IOException e) {
                    System.err.println("Error reading file: " + e.getMessage());
                }
                break;
            default:
                System.out.println("Invalid choice");
        }

        scanner.close();
    }

    public static void hashString(String input) {
        try {
            System.out.println("Input String: " + input);
            System.out.println("MD5 Hash: " + hash(input.getBytes(), "MD5"));
            System.out.println("SHA-1 Hash: " + hash(input.getBytes(), "SHA-1"));
            System.out.println("SHA-256 Hash: " + hash(input.getBytes(), "SHA-256"));
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm not found: " + e.getMessage());
        }
    }

    public static void hashFile(String filename) throws IOException {
        try (FileInputStream fis = new FileInputStream(filename)) {
            byte[] buffer = new byte[1024];
            int bytesRead;

            MessageDigest md5Digest = MessageDigest.getInstance("MD5");
            MessageDigest sha1Digest = MessageDigest.getInstance("SHA-1");
            MessageDigest sha256Digest = MessageDigest.getInstance("SHA-256");

            while ((bytesRead = fis.read(buffer)) != -1) {
                md5Digest.update(buffer, 0, bytesRead);
                sha1Digest.update(buffer, 0, bytesRead);
                sha256Digest.update(buffer, 0, bytesRead);
            }

            System.out.println("Input File: " + filename);
            System.out.println("MD5 Hash: " + toHex(md5Digest.digest()));
            System.out.println("SHA-1 Hash: " + toHex(sha1Digest.digest()));
            System.out.println("SHA-256 Hash: " + toHex(sha256Digest.digest()));
        } catch (NoSuchAlgorithmException e) {
            System.err.println("Hashing algorithm not found: " + e.getMessage());
        }
    }

    private static String hash(byte[] input, String algorithm) throws NoSuchAlgorithmException {
        MessageDigest messageDigest = MessageDigest.getInstance(algorithm);
        byte[] digest = messageDigest.digest(input);
        return toHex(digest);
    }

    private static String toHex(byte[] bytes) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : bytes) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }
}
