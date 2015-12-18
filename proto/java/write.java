import java.io.*;
import java.net.*;
import PHT.*;

class write {
  // Main function: Send data to the server on localhost:3303 
  public static void main(String[] args) throws Exception {
      // PHTmessage instance:
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();

    // PHTmessage TYPE:
    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);
    System.out.println(message.hasType());

    // Definition of a Proposals with given fields:
    ProposalsOuterClass.Proposals.Builder proposal =  ProposalsOuterClass.Proposals.newBuilder();
    proposal.setAbstract("ahahahahah");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);
    proposal.setProposalType(ProposalTypeOuterClass.ProposalType.TOO);

    // Adding proposal to the message
    message.addProposal(proposal);
    System.out.println(message.build().toString());

    // Preparing transmission:
    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos);
    // Serialization
    message.build().writeTo(ps);

    // Length of binary string
    byte [] test;
    test = baos.toByteArray();
    System.out.println(test.length);

    // TCP/IP connection
    Socket mys;
    mys = new Socket("localhost",3303);
    DataOutputStream msg = new DataOutputStream(mys.getOutputStream());
    // Data sending:
    msg.writeInt(test.length);
    msg.flush();
    msg.write(test);
    msg.flush();
    //msg.close();

    // reply from the server:
    /*mys = new Socket("localhost",3303);*/
    DataInputStream rep = new DataInputStream(mys.getInputStream());
    int l;
    l = rep.readInt();
    System.out.println(l);
    byte[] reply = new byte[l];
    rep.readFully(reply,0,l);
    rep.close();

    System.out.println(reply.length);
    PHTmessageOuterClass.PHTmessage m2 = PHTmessageOuterClass.PHTmessage.parseFrom(reply);
    System.out.println(m2.toString());
  }
}
