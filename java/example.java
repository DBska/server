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
    proposal.setAbstract("My new survey abstract");
    proposal.setProposalStatus(ProposalStatusOuterClass.ProposalStatus.Draft);
    proposal.setProposalType(ProposalTypeOuterClass.ProposalType.TOO);

    // Adding CoAuthors
    CoAuthorsOuterClass.CoAuthors.Builder coa = CoAuthorsOuterClass.CoAuthors.newBuilder();
    coa.setAuthorId(57);
    proposal.setMCoAuthors(coa);

    // Adding Science Goals
    ScienceGoalsOuterClass.ScienceGoals.Builder sciencegoals = ScienceGoalsOuterClass.ScienceGoals.newBuilder();
    sciencegoals.setFrequence(117.10);
    sciencegoals.setInstrumentConfigurations("Twin interferometer");
    sciencegoals.setMoreInfo("--");
    sciencegoals.setTargetDetails("Jupiter and its satellites");
    proposal.setMScienceGoals(sciencegoals);

    // Adding SupportingDocuments
    SupportingDocumentsOuterClass.SupportingDocuments.Builder supdocs = SupportingDocumentsOuterClass.SupportingDocuments.newBuilder();

    String scifile = "1457_e.pdf";	
    supdocs.setScientificJustification("1457_e.pdf");
    
    String techfile = "2784600.jpg";	
    supdocs.setTechnicalJustification("2784600.jpg");

    String preprint = "text.txt";	
    supdocs.setPreprints("text.txt");
    proposal.setMSupportingDocuments(supdocs);

    // Sending proposal
    StringBuffer error = new StringBuffer("");
    StringBuffer proposal_id = new StringBuffer("");
    proposal_id = apioda.insertNewProposal(proposal.build(),error);
  
    System.out.println("Error new insert: "+error);
    System.out.println("Proposal ID: "+proposal_id);

	
    	
    // Inserting supporting documents for given proposal_id:
    int pid = Integer.parseInt("5");
    System.out.println("Val: "+pid);
    apioda.uploadFile(pid,"./supportingDocuments/",scifile);
    apioda.uploadFile(pid,"./supportingDocuments/",techfile);
    apioda.uploadFile(pid,"./supportingDocuments/",preprint);
/*
    // Requesting proposal with ID = my_proposal_ID
    int my_proposal_id = 9;
    ProposalsOuterClass.Proposals pID = apioda.getProposalWithID(my_proposal_id);
    ScienceGoalsOuterClass.ScienceGoals sg = pID.getMScienceGoals();
 

    System.out.println("Retrieved proposal: "+pID.getProposalId());
    System.out.println("ScienceGoals Frequency: "+sg.getFrequence());

    
    proposal.setAbstract("testAbs");
    int id = Integer.parseInt(proposal_id.toString());
    proposal.setProposalId(id);
    //System.out.println(proposal.getAbstract());
    apioda.modifyProposal(proposal.build(),error);
    System.out.println("Error modify: "+error);

    Vector<ProposalsOuterClass.Proposals> p_l = new Vector<ProposalsOuterClass.Proposals>();
    System.out.println("Requesting proposals list with status: "+PHT.ProposalStatusOuterClass.ProposalStatus.Draft);
    p_l = apioda.requestProposalsWithStatus(PHT.ProposalStatusOuterClass.ProposalStatus.Draft);

    System.out.println("Found : "+p_l.size());
   */ 
  }
}
