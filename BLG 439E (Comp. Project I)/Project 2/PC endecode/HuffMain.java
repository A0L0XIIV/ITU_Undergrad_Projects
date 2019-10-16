import java.io.*;
import java.util.*;

public class HuffMain {
    public static PriorityQueue<Node> q;
    public static HashMap<Character, String> charToCode;
    public static HashMap<String, Character> codeToChar;

    @SuppressWarnings("resource")
    public static void main(String[] args) throws FileNotFoundException {
        // Read all the contents of the file
        String text = new Scanner(new File("text.txt")).useDelimiter("\\A").next(); 
        // Count the frequency of all the characters
        HashMap<Character, Integer> dict = new HashMap<Character, Integer>();
        for(int i = 0; i < text.length(); i++) {
            char a = text.charAt(i);
            if(dict.containsKey(a))
                dict.put(a, dict.get(a)+1);
            else
                dict.put(a, 1);
        }

        // Create a forest (group of trees) by adding all the nodes to a priority queue
        q = new PriorityQueue<Node>(100, new FrequencyComparator());
        int n = 0;
        for(Character c : dict.keySet()) {
            q.add(new Node(c, dict.get(c)));
            n++;
        }
        Node root = huffmain(n);
        buildTable(root);

        String compressed = compress(text);
        saveToFile(compressed);

        String decompressed = decompress(compressed);
        writeToFile(decompressed);
    }

    // This method builds the tree based on the frequency of every characters 
    public static Node huffmain(int n) {
        Node x, y;
        for(int i = 1; i <= n-1; i++) {
            Node z = new Node();
            z.left = x = q.poll();
            z.right = y = q.poll();
            z.freq = x.freq + y.freq;
            q.add(z);
        }
        return q.poll();
    }

    // This method builds the table for the compression and decompression
    public static void buildTable(Node root) {
        charToCode = new HashMap<Character, String>();
        codeToChar = new HashMap<String, Character>();
        postorder(root, new String());
    }

    // This method is used to traverse from ROOT-to-LEAVES
    public static void postorder(Node n, String s) {
        if(n == null)
            return;
        postorder(n.left, s+"0");
        postorder(n.right, s+"1");

        // Visit only nodes with keys
        if (!Character.toString(n.alpha).equals("&#092;&#048;")){
            System.out.println("{" + n.alpha + ":" + s + "}");
            charToCode.put(n.alpha, s);
            codeToChar.put(s, n.alpha);
        }
    }

    //assuming tree and dictionary are already built...
    public static String compress(String s) {
        String c = new String();
        for(int i = 0; i < s.length(); i++)
            c = c + charToCode.get(s.charAt(i));
        return c;
    }

    //assuming tree and dictionary are already built...
    public static String decompress(String s) {
    String temp = new String();
    String result = new String();
    for(int i = 0; i < s.length(); i++) {
        temp = temp + s.charAt(i);
        Character c = codeToChar.get(temp);
        if(c!=null && c!=0) {
            result = result + c;
            temp = "";
        }
    }
    return result;
}
    public static void saveToFile(String l) throws FileNotFoundException {
        PrintWriter oFile = new PrintWriter("text.txt.huf");
        oFile.print(charToCode.size());
        for(char s : charToCode.keySet())
            oFile.println("{" +s + ":" + charToCode.get(s)+ "}");
        oFile.println(l);
        oFile.close();
    }

    public static void writeToFile(String i) throws FileNotFoundException {
        PrintWriter iFile = new PrintWriter("note.txt");
        iFile.print(codeToChar.size());
        for (String s : codeToChar.keySet())
            iFile.println("{" +s + ":" + codeToChar.get(s)+ "}");
        iFile.println(i);
        iFile.close();
    }
}
//Creating a Node Class    
class Node {
    public char alpha;
    public int freq;
    public Node left, right;

    public Node(char a, int f) {
        alpha = a;
        freq = f;
    }  
    public Node() {
    } 
    public String toString() {
        return alpha + " " + freq;
    }    
}     
class FrequencyComparator implements Comparator<Node> {
    public int compare(Node a, Node b) {
        int freqA = a.freq;
        int freqB = b.freq;
        return freqA-freqB;
    }

}
