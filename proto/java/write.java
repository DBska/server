import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import PHT.*;

class write {
  // Main function:  Reads the entire address book from a file,
  //   adds one person based on user input, then writes it back out to the same
  //   file.
  public static void main(String[] args) throws Exception {
    PHTmessageOuterClass.PHTmessage.Builder message = PHTmessageOuterClass.PHTmessage.newBuilder();


    message.setType(PHTmessageOuterClass.PHTmessage.MessageType.DATA);

    ProposalsOuterClass.Proposals.Builder proposal =  ProposalsOuterClass.Proposals.newBuilder();
    proposal.setAbstract("ahahahahah");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);

    message.addProposal(proposal);

    // Write the new address book back to disk.
    FileOutputStream output = new FileOutputStream("file_name");
    message.build().writeTo(output);
    output.close();
  }
}
