import java.io.*;
import java.net.*;
import java.lang.*;
import java.util.Vector;
import PHT.*;

class example {
  // Compile with "javac example" 
  public static void main(String[] args) throws Exception {
    // Definition of a Proposals with given fields:
    ProposalsOuterClass.Proposals.Builder proposal =  ProposalsOuterClass.Proposals.newBuilder();
    proposal.setAbstract("ahaha????hahah");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);
    proposal.setProposalType(ProposalTypeOuterClass.ProposalType.TOO);

    // Sending proposal
    StringBuffer error = new StringBuffer("");
    StringBuffer proposal_id = new StringBuffer("");
    proposal_id = apioda.insertNewProposal(proposal.build(),error);
  
    System.out.println("Error new insert: "+error);
    System.out.println("Proposal ID: "+proposal_id);

    proposal.setAbstract("eheheheheheh");
    int id = Integer.parseInt(proposal_id.toString());
    proposal.setProposalId(id);
    //System.out.println(proposal.getAbstract());
    apioda.modifyProposal(proposal.build(),error);
    System.out.println("Error modify: "+error);

    Vector<ProposalsOuterClass.Proposals> p_l = new Vector<ProposalsOuterClass.Proposals>();
    System.out.println("Requesting proposals list with status: "+PHT.ProposalStatusOuterClass.ProposalStatus.Draft);
    p_l = apioda.requestProposalsWithStatus(PHT.ProposalStatusOuterClass.ProposalStatus.Draft);

    System.out.println("Found : "+p_l.size());
  }
}
