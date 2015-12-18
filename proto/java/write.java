import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.OutputStream;
import java.io.*;

import java.net.*;
import PHT.*;

class write {
  // Main function:  Reads the entire address book from a file,
  //   adds one person based on user input, then writes it back out to the same
  //   file.
  public static void main(String[] args) throws Exception {
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();


    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);

    System.out.println(message.hasType());

    ProposalsOuterClass.Proposals.Builder proposal =  ProposalsOuterClass.Proposals.newBuilder();
    proposal.setAbstract("ahahahahah");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);
    proposal.setProposalType(ProposalTypeOuterClass.ProposalType.TOO);

    message.addProposal(proposal);
    System.out.println(message.build().toString());

    ByteArrayOutputStream baos = new ByteArrayOutputStream();
    PrintStream ps = new PrintStream(baos); 
    message.build().writeTo(ps);
    byte [] test;
    test = baos.toByteArray();
    System.out.println(test.length);


    Socket mys;
    mys = new Socket("localhost",3303);
    DataOutputStream msg = new DataOutputStream(mys.getOutputStream());
    
    msg.writeInt(test.length);
    msg.flush();
    msg.write(test);
    msg.flush();
    msg.close();


    // Write the new address book back to disk.
    //FileOutputStream output = new FileOutputStream("file_name");
    //message.build().writeTo(output);
    //output.close();
  }
}
