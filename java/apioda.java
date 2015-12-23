import java.io.*;
import java.net.*;
import PHT.*;

class apioda {
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
    Socket mys;
    mys = new Socket("localhost",3303);
    DataOutputStream msg = new DataOutputStream(mys.getOutputStream());
    // Data sending:
    //System.out.println("Sending message of "+tmp.length);
    msg.writeInt(tmp.length);
    msg.flush();
    msg.write(tmp,0,tmp.length);
    msg.flush();
    StringBuffer proposal_id = new StringBuffer("not set");

    // reply from the server:
    DataInputStream rep = new DataInputStream(mys.getInputStream());
    int l_rep;
    l_rep = rep.readInt();
    //System.out.println("->"+l_rep);
    byte[] reply = new byte[l_rep];
    rep.readFully(reply,0,l_rep);

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

    mys.close();

    return proposal_id;
  }


    public static void modifyProposal(ProposalsOuterClass.Proposals proposal, String error_message) throws Exception {
    // PHTmessage instance:
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();
    error_message = "no error";
    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);
    //System.out.println(message.hasType());

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
    Socket mys;
    mys = new Socket("localhost",5200);
    DataOutputStream msg = new DataOutputStream(mys.getOutputStream());
    // Data sending:
    msg.writeInt(tmp.length);
    msg.flush();
    msg.write(tmp);
    msg.flush();
    //msg.close();

    // reply from the server:
    DataInputStream rep = new DataInputStream(mys.getInputStream());
    int l_rep;
    l_rep = rep.readInt();
    System.out.println(l_rep);
    byte[] reply = new byte[l_rep];
    rep.readFully(reply,0,l_rep);
    //rep.close();

    //System.out.println(reply.length);
    //PHTmessageOuterClass.PHTmessage m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    //System.out.println(m2.toString());
    PHTmessageOuterClass.Answer a;
    if (message.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        a = message.getAnswer();
        error_message = a.getAnswer();
    }
  }
}
