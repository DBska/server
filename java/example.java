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

    // Sending proposal
    StringBuffer error = new StringBuffer("");
    StringBuffer proposal_id = new StringBuffer("");
    proposal_id = apioda.insertNewProposal(proposal.build(),error);
  
    System.out.println("Error: "+error);
    System.out.println("Proposal ID: "+proposal_id);
  }
}
