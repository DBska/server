import java.io.*;
import java.net.*;
import PHT.*;

class apioda {
  // Main function: Send data to the server on localhost:5200 
  public static String insertNewProposal(ProposalsOuterClass.Proposals proposal, String error_message) throws Exception {
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
    String proposal_id = "not set";
    PHTmessageOuterClass.Answer a;
    if (message.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ANSWER) 
    {
        a = message.getAnswer();
        proposal_id = a.getAnswer(); 
    }
    if (message.getType()== PHTmessageOuterClass.PHTmessage.MessageType.ERROR)
    {
        a = message.getAnswer();
        error_message = a.getAnswer();
    }

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
