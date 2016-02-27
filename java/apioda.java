import org.apache.commons.io.FileUtils;
import java.io.*;
import java.net.*;
import java.util.Vector;
import PHT.*;

public class apioda {
  public static void print(String file, byte [] what) throws Exception {
        FileOutputStream output = new FileOutputStream(file);
        output.write(what);
        output.close();
  }
  public static Socket connect() throws Exception {
        Socket socket;
        socket = new Socket("localhost",3303);
        //socket = new Socket("spock.oats.inaf.it",5200);

        return socket;
    }
  public static int byteArrayToInt(byte[] b) 
    {
    return   b[3] & 0xFF |
            (b[2] & 0xFF) << 8 |
            (b[1] & 0xFF) << 16 |
            (b[0] & 0xFF) << 24;
    }    
  public static byte[] toByteArray(int value) {
    //System.out.println("int "+value);
    //System.out.println("aa "+(byte)(value>>24));
    //System.out.println("bb "+(byte)(value>>16));
    //System.out.println("cc "+(byte)(value>>8));
    //System.out.println("dd "+(byte)(value));
    
    //byte [] bb = new byte[] { (byte)(value >> 24),
    //    (byte)(value >> 16),
    //    (byte)(value >> 8),
    //    (byte)value };
    //System.out.println("back "+byteArrayToInt(bb));

    return new byte[] { 
        (byte)(value >> 24),
        (byte)(value >> 16),
        (byte)(value >> 8),
        (byte)value };
    }
  public static void writeToSocket(DataOutputStream out, byte[] msg) throws Exception {
        //send
        System.out.println("IN byte[] DataOutputStream");
        int msg_l = msg.length;
        System.out.println("Length: "+msg_l);
        byte [] result = toByteArray(msg_l);

        //FileOutputStream output2 = new FileOutputStream("blobOUTlen.bin");
        //output2.write(result);
        //output2.close();

        out.write(result);
        out.flush();
        out.write(msg);
        out.flush();

        //FileOutputStream output = new FileOutputStream("blobOUT.bin");
        //output.write(msg);
        //output.close();

  }
  public static byte [] readFromSocket(DataInputStream in) throws Exception {
        
        System.out.println("READ byte[] DataInputStream");
        byte [] bb =  new byte[4];
        in.readFully(bb,0,4);
        int cn = byteArrayToInt(bb);
        /*for(byte b:bb)
         {
            // convert byte to character
            char c=(char)b;
            
            // prints character
            System.out.print(c);
         }*/

        System.out.println("Received message length: "+cn);
        byte [] buffer = new byte[cn];
        in.readFully(buffer,0,cn);
        //print("inside.bin",buffer);
        //String reply = new String(buffer, 0, cn);
        System.out.println("Message Length: "+buffer.length);
    
        return buffer;
  }

  // Upload a file to the server
  public static void uploadFile(int pid,String path_file_name) throws Exception
  {
    System.out.println("Uploading file: "+Integer.toString(pid)+path_file_name);
    // Reading path_file_name. this is the full path plus name: ie /home/my_path/to_file/filename.ppp
    File file = new File(path_file_name);
    byte[] fBytes = FileUtils.readFileToByteArray(file);
    //String fileContent = new String(fBytes);
    //System.out.println(fileContent);
  }


  // Return proposal with given id 
  public static ProposalsOuterClass.Proposals getProposalWithID(int pid)  throws Exception   
  {
    ProposalsOuterClass.Proposals p_v;
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();
    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.QUERY);
    //System.out.println("222 "+message.hasType());

    PHTmessageOuterClass.Query.Builder query = PHTmessageOuterClass.Query.newBuilder();
    
    int i_status = pid * (-1); // negative number to distinquish on server side from a status 
    query.setQuery(i_status);
    System.out.println("Searching for proposal with ID: "+pid);

    // Adding query to the message
    message.setQuery(query);
    //System.out.println(message.build().toString());

    // Preparing transmission:
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos);
    
    // Serialization
    message.build().writeTo(ps);

    // Length of binary string
    byte [] tmp;
    tmp = baos.toByteArray();
    //System.out.println(tmp.length);

    // TCP/IP connection
    Socket socket = connect();
    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    // Data sending:
    //System.out.println("Sending message of "+tmp.length);
    writeToSocket(out,tmp);

    // reply from the server:
    DataInputStream in = new DataInputStream(socket.getInputStream());
    byte [] reply = readFromSocket(in);

    System.out.println("--> "+reply.length);
    PHTmessageOuterClass.PHTmessage m2;
    print("arrived.bin",reply);
    m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    System.out.println("--> HERE");
    //System.out.println("zz "+m2.toString());
    //System.out.println(m2.getType());
    PHTmessageOuterClass.Answer a;
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.DATA)
    {
        //a = m2.getAnswer();
        //error_message.delete(0,error_message.length()).append(a.getAnswer());
    }
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        System.out.println("Not yet implemented..");
    }

    p_v = m2.getProposal(0);

    socket.close();

    return p_v;
  }


  // Main function: Send data to the server on localhost:5200 
  public static StringBuffer insertNewProposal(ProposalsOuterClass.Proposals proposal, StringBuffer error_message) throws Exception {
    // PHTmessage instance:
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();
    error_message.delete(0,error_message.length()).append("no error");
    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);
    //System.out.println("222 "+message.hasType());

    // Adding proposal to the message
    message.addProposal(proposal);
    System.out.println(message.build().toString());

    // Preparing transmission:
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos);
    
    // Serialization
    message.build().writeTo(ps);
        //FileOutputStream outputT = new FileOutputStream("serial.bin");
        //outputT.write(baos.toByteArray());
        //outputT.close();


    // Length of binary string
    byte [] tmp;
    tmp = baos.toByteArray();
    System.out.println("insert proposal message length: "+tmp.length);

    // TCP/IP connection
    Socket socket = connect();
    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    // Data sending:
    //System.out.println("Sending message of "+tmp.length);
    writeToSocket(out,tmp); 

    // reply from the server:
    DataInputStream in = new DataInputStream(socket.getInputStream());
    StringBuffer proposal_id = new StringBuffer("not set");
    byte [] reply = readFromSocket(in);

    //System.out.println(reply.length);
    PHTmessageOuterClass.PHTmessage m2;
    m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    //System.out.println("zz "+m2.toString());
    //System.out.println(m2.getType());
    PHTmessageOuterClass.Answer a;
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ANSWER) 
    {
        //System.out.println("here\n");
        a = m2.getAnswer();
        //System.out.println("333 "+a.getAnswer());
        proposal_id.delete(0,proposal_id.length()).append(a.getAnswer()); 
    }
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        a = m2.getAnswer();
        error_message.delete(0,error_message.length()).append(a.getAnswer());
    }

    socket.close();

    return proposal_id;
  }


    public static void modifyProposal(ProposalsOuterClass.Proposals proposal, StringBuffer error_message) throws Exception {
    // PHTmessage instance:
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();
    error_message.delete(0,error_message.length()).append("no error");
    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);
    //System.out.println("222 "+message.hasType());

    // Adding proposal to the message
    message.addProposal(proposal);
    //System.out.println(message.build().toString());

    // Preparing transmission:
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos);
    
    // Serialization
    message.build().writeTo(ps);

    // Length of binary string
    byte [] tmp;
    tmp = baos.toByteArray();
    //System.out.println(tmp.length);

    // TCP/IP connection
    Socket socket = connect();
    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    // Data sending:
    //System.out.println("Sending message of "+tmp.length);
    writeToSocket(out,tmp);

    // reply from the server:
    DataInputStream in = new DataInputStream(socket.getInputStream());
    byte [] reply = readFromSocket(in);

    //System.out.println(reply.length);
    PHTmessageOuterClass.PHTmessage m2;
    m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    //System.out.println("zz "+m2.toString());
    //System.out.println(m2.getType());
    PHTmessageOuterClass.Answer a;
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        a = m2.getAnswer();
        error_message.delete(0,error_message.length()).append(a.getAnswer());
    }

    socket.close();
  }

  public static Vector<ProposalsOuterClass.Proposals> requestProposalsWithStatus(ProposalStatusOuterClass.ProposalStatus status)  throws Exception   
  {
    Vector<ProposalsOuterClass.Proposals> p_v = new Vector<ProposalsOuterClass.Proposals>();
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();
    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.QUERY);
    //System.out.println("222 "+message.hasType());

    PHTmessageOuterClass.Query.Builder query = PHTmessageOuterClass.Query.newBuilder();
    
    int i_status = status.getNumber() + 1; // +1 is for mysql that starts counting from 1 and not 0
    query.setQuery(i_status);
    System.out.println("Searching for proposal with status: "+status.getNumber());

    // Adding query to the message
    message.setQuery(query);
    //System.out.println(message.build().toString());

    // Preparing transmission:
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos);
    
    // Serialization
    message.build().writeTo(ps);

    // Length of binary string
    byte [] tmp;
    tmp = baos.toByteArray();
    //System.out.println(tmp.length);

    // TCP/IP connection
    Socket socket = connect();
    DataOutputStream out = new DataOutputStream(socket.getOutputStream());
    // Data sending:
    //System.out.println("Sending message of "+tmp.length);
    writeToSocket(out,tmp);

    // reply from the server:
    DataInputStream in = new DataInputStream(socket.getInputStream());
    byte [] reply = readFromSocket(in);

    System.out.println("--> "+reply.length);
    PHTmessageOuterClass.PHTmessage m2;
    print("arrived.bin",reply);
    m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    System.out.println("--> HERE");
    //System.out.println("zz "+m2.toString());
    //System.out.println(m2.getType());
    PHTmessageOuterClass.Answer a;
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.DATA)
    {
        //a = m2.getAnswer();
        //error_message.delete(0,error_message.length()).append(a.getAnswer());
    }
    if (m2.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        System.out.println("Not yet implemented..");
    }

    System.out.println("Proposals count: "+m2.getProposalCount());
    int n_p = m2.getProposalCount();
    for (int i=0; i<n_p; i++)
    {
        ProposalsOuterClass.Proposals prop = m2.getProposal(i);
        p_v.add(prop);
    }

    socket.close();

    return p_v;
  }

}
