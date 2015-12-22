import java.io.*;
import java.net.*;
import PHT.*;

class example {
  // Compile with "javac example" 
  public static void main(String[] args) throws Exception {
    // Definition of a Proposals with given fields:
    ProposalsOuterClass.Proposals.Builder proposal =  ProposalsOuterClass.Proposals.newBuilder();
    proposal.setAbstract("ahahahahah");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);
    proposal.setProposalType(ProposalTypeOuterClass.ProposalType.TOO);
  }
}
