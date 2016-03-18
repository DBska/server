#include "connectDB.h"
#include <boost-optional.h>

//string writeToDB(data_s dat)
string writeToDB(data_s dat, session &sql)
{
    string proposal_id = "";
    // Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
    // should be put in the for(i) above.
    //session sql(mysql, use_db);
    transaction tr(sql);

    // before inserting, printing the currente number of Proposals
    int count;
    sql<<"select count(*) from Proposals", into(count);
    cout<<"Table Proposals has "<<count<<" entries"<<endl;

    // Inserting the data
    //sql<<"insert into Proposals (abstract) values(:abstractp)", use(proposal.abstract());
    //for (int i=0; i<command.size(); i++)
    //{
    //    sql<<command[i];
    //}
    // Building commands. There are two possibilities: 1) a new insertion (no
    // proposal_id yet) or 2) modification of an existing proposal (proposal_id
    // known)
    bool new_insertion = true;

    // Check wheater this is a new proposal or an update of an old one
    int nf = dat.name[0].size();
    for (int i=0; i<nf; i++)
    {
        if ( dat.name[0][i] == "proposal_id" )
            new_insertion = false;
    }


    
    if ( new_insertion ) // new insertion and assignement of proposal_id.
    {
        stringstream cmd;
        // First insertion is Proposal
        cmd<<"INSERT INTO "<<dat.table[0]<<" (";
        int nf = dat.name[0].size();
        for (int i=0; i<nf-1; i++)
        {
            cmd<<dat.name[0][i]<<",";
        }
        cmd<<dat.name[0][nf-1]<<") VALUES (\"";
        for (int i=0; i<nf-1; i++)
        {
            cmd<<dat.value[0][i]<<"\",\"";
        }
        cmd<<dat.value[0][nf-1]<<"\");";

        cout<<cmd.str()<<endl;
        sql<<cmd.str();
        // Retrieving newly assigned proposal_id
        rowset<row> rs = (sql.prepare << "select proposal_id from Proposals order by proposal_id desc limit 1");

        // iteration through the resultset:
        stringstream s_tmp;
        int r = 1;
        for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
        {
            row const& row = *it;

            // dynamic data extraction from each row:
            s_tmp<< row.get<int>(0);
            r++;
        }
        proposal_id = s_tmp.str();
        cout<<"proposal_id: "<<proposal_id<<endl;
        cmd.str( string() );

        int nt = dat.table.size();
        for (int t=1; t<nt; t++)
        {
            cmd<<"INSERT INTO "<<dat.table[t]<<" (";
            int nf = dat.name[t].size();
            cmd<<"proposal_id,";
            for (int i=0; i<nf-1; i++)
            {
                cmd<<dat.name[t][i]<<",";
            }
            cmd<<dat.name[t][nf-1]<<") VALUES (\"";
            cmd<<proposal_id<<"\",\"";
            for (int i=0; i<nf-1; i++)
            {
                cmd<<dat.value[t][i]<<"\",\"";
            }
            cmd<<dat.value[t][nf-1]<<"\");";

            cout<<cmd.str()<<endl;
            sql<<cmd.str();
            cmd.str( string() );
        }
    }
    else // a modification is requested. In mysql the command is:
         // update tab_name set col1=val1 where proposal_id=ID;
         // for each value that must be changed. The command can be shortened,
         // but for the time being this is ok.
    {
        stringstream cmd; // This variable stores update command for each table's fields

        // The proposal_id is available inside the message.
        int nf = dat.name[0].size();
        for (int i=0; i<nf; i++)
        {
            if ( dat.name[0][i] == "proposal_id" )
                proposal_id = dat.value[0][i];
        }
        cout<<"Arrived a request for updating proposal_id "<<proposal_id<<endl;

        // Updating requested values:
        int nt = dat.table.size();
        for (int t=0; t<nt; t++)
        {
            int nf = dat.name[t].size();
            for (int i=0; i<nf; i++)
            {
                if ( dat.name[0][i] == "proposal_id" ) continue;
                cmd<<"UPDATE "<<dat.table[t]<<" SET ";
                cmd<<dat.name[t][i]<<"=\""<<dat.value[t][i]<<"\" WHERE proposal_id="<<proposal_id<<";";
                // Executing mysql command 
                cout<<cmd.str()<<endl;
                sql<<cmd.str();
                cmd.str( string() );  // cleaning command string
            }
        }
        proposal_id = ""; // No proposal_id has been set
    }


    sql<<"select count(*) from Proposals", into(count);
    cout<<"Table Proposals now has "<<count<<" entries"<<endl;

    // Printing the new table on screen
    /*
    rowset<row> rs = (sql.prepare << "select proposal_id, abstract from Proposals");

    // iteration through the resultset:
    int r = 1;
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it)
    {
        row const& row = *it;

        // dynamic data extraction from each row:
        cout << "ID: " << row.get<int>(0)
             << " Abstract: " << row.get<string>(1)  << endl;
        r++;
    }
    */
    tr.commit();
    sql.close();

    return proposal_id;
}

//Proposals * readProposalFromDB(int pid)
Proposals * readProposalFromDB(int pid, session &sql)
{
    cout<<"Reading DB..\n";

    //session sql(mysql, use_db);

    // Extracting the total number of proposals and storing each proposal_id in
    // vector<int> p_id
    stringstream cmd;
    
    cout<<"Retrieving proposal "<<pid<<endl;
    // Proposals
    Proposals *p = new Proposals;
    string abstract;
    boost::optional<string> more_info;
    string pst;
    string pty;
    sql<<"select abstract, more_info, proposal_status, proposal_type from Proposals where proposal_id=:id;", use(pid), 
    into(abstract), into(more_info), into(pst), into(pty);

    p->set_proposal_id(pid);
    p->set_abstract(abstract);
    if (more_info.is_initialized())
    {
        p->set_more_info(more_info.get());
    }
        
    ProposalStatus proposal_status;
    ProposalType proposal_type;
    switch ( atoi(pst.c_str()) )
    {
        case PHT::Draft:
            proposal_status = PHT::Draft;
            break;
        case PHT::Accepted:
            proposal_status = PHT::Accepted;
            break;
        case PHT::Rejected:
            proposal_status = PHT::Rejected;
            break;
        case PHT::Submitted:
            proposal_status = PHT::Submitted;
            break;
        case PHT::Merged:
            proposal_status = PHT::Merged;
            break;
    }
    p->set_proposal_status(proposal_status);
        
    switch ( atoi(pty.c_str()) )
    {
        case PHT::TOO:
            proposal_type = PHT::TOO;
            break;
        case PHT::DDT:
            proposal_type = PHT::DDT;
            break;
        case PHT::PI:
            proposal_type = PHT::PI;
            break;
        case PHT::KeyScienceProject:
            proposal_type = PHT::KeyScienceProject;
            break;
    }
    p->set_proposal_type(proposal_type);

    //tab_name.push_back("CoAuthors");
    CoAuthors *coa = new CoAuthors;
   
    int author_id, proposal_id, coAuthorsID;
    sql<<"select author_id, proposal_id, coAuthorsID from CoAuthors where proposal_id=:id;", use(pid), 
            into(author_id), into(proposal_id), into(coAuthorsID);

    coa->set_author_id(author_id);
    //coa->set_proposal_id(proposal_id); // not necessary
    coa->set_coauthorsid(coAuthorsID);

    p->set_allocated_m_coauthors(coa);
    //tab_name.push_back("ProposalEditors");
    ProposalEditors *ped = new ProposalEditors;
    int isPI, proposalEditorsID;
    string aid;
    sql<<"select author_id, isPI, more_info, proposal_id from ProposalEditors where proposal_id=:id;", use(pid), 
        into(aid), into(isPI), into(more_info), into(proposal_id);

    ped->set_author_id(aid);
    ped->set_ispi(isPI);
    if (more_info.is_initialized())
    {
        ped->set_more_info(more_info.get()); // boost
    }
    ped->set_proposal_id(proposal_id);

    p->set_allocated_m_proposaleditors(ped);
    //tab_name.push_back("Reviews");
    Reviews *rev = new Reviews;

    string grade_rank, review_comments;
    int reviewer_id, reviewsID;
    sql<<"select grade_rank, proposal_id, review_comments, reviewer_id from Reviews where proposal_id=:id;", use(pid), 
        into(grade_rank), into(proposal_id), into(review_comments), into(reviewer_id);

    rev->set_grade_rank(grade_rank);
    rev->set_proposal_id(proposal_id);
    rev->set_review_comments(review_comments);
    rev->set_reviewer_id(reviewer_id);

    p->set_allocated_m_reviews(rev);
    //tab_name.push_back("ScienceGoals");
    ScienceGoals *scg = new ScienceGoals;

    double frequence;
    string ins_conf, tgt_det;
    sql<<"select frequence, instrument_configurations, more_info, target_details from ScienceGoals where proposal_id=:id;", use(pid), 
        into(frequence), into(ins_conf), into(more_info), into(tgt_det);

    scg->set_frequence(frequence);
    scg->set_instrument_configurations(ins_conf);
    if (more_info.is_initialized())
    {
        scg->set_more_info(more_info.get()); //boost
    }
    scg->set_target_details(tgt_det);

    p->set_allocated_m_sciencegoals(scg);
    //tab_name.push_back("SupportingDocuments");
    SupportingDocuments *sd = new SupportingDocuments;

    string prep, sc_j, tec_j;
    sql<<"select preprints, scientific_justification, technical_justification from SupportingDocuments where proposal_id=:id;", use(pid), 
        into(prep), into(sc_j), into(tec_j);

    sd->set_preprints(prep);
    sd->set_scientific_justification(sc_j);
    sd->set_technical_justification(tec_j);

    p->set_allocated_m_supportingdocuments(sd);
    //tab_name.push_back("TACReviews");
    TACReviews *tr = new TACReviews;

    string com, fg;
    int tac_id;
    sql<<"select comments, final_grade, tac_id from TACReviews where proposal_id=:id;", use(pid), 
        into(com), into(fg), into(tac_id);

    tr->set_comments(com);
    tr->set_final_grade(fg);
    tr->set_tac_id(tac_id);
    p->set_allocated_m_tacreviews(tr);
    // Adding proposal to the list
    
    sql.close();

    return p;
}


//vector<Proposals *> readAllProposalsFromDB(int p_status)
vector<Proposals *> readAllProposalsFromDB(int p_status, session &sql)
{
    cout<<"Reading DB..\n";
    vector<Proposals *> p_w_s;
    vector<string> tab_name;

    // Inserting all DB table names for PHT
    tab_name.push_back("Proposals");
    tab_name.push_back("CoAuthors");
    tab_name.push_back("ProposalEditors");
    tab_name.push_back("Reviews");
    tab_name.push_back("ScienceGoals");
    tab_name.push_back("SupportingDocuments");
    tab_name.push_back("TACReviews");

    //session sql(mysql, use_db);

    // Extracting the total number of proposals and storing each proposal_id in
    // vector<int> p_id
    stringstream cmd;
    
    cmd<<"select proposal_id from Proposals where proposal_status = "<<p_status<<";";
    //cout<<cmd.str()<<endl;
    vector<int> ps(2000);
    sql << cmd.str(), into(ps);
    cout<<"Found "<<ps.size()<<" proposals\n";

    for (int id=0; id<ps.size(); id++)
    {
        cout<<"Retrieving proposal "<<ps[id]<<endl;
        // Proposals
        Proposals *p = new Proposals;
        string abstract;
        boost::optional<string> more_info;
        string pst;
        string pty;
        sql<<"select abstract, more_info, proposal_status, proposal_type from Proposals where proposal_id=:id;", use(ps[id]), 
            into(abstract), into(more_info), into(pst), into(pty);

        p->set_proposal_id(ps[id]);
        p->set_abstract(abstract);
        if (more_info.is_initialized())
        {
            p->set_more_info(more_info.get());
        }
        
        ProposalStatus proposal_status;
        ProposalType proposal_type;
        switch ( atoi(pst.c_str()) )
        {
            case PHT::Draft:
                proposal_status = PHT::Draft;
                break;
            case PHT::Accepted:
                proposal_status = PHT::Accepted;
                break;
            case PHT::Rejected:
                proposal_status = PHT::Rejected;
                break;
            case PHT::Submitted:
                proposal_status = PHT::Submitted;
                break;
            case PHT::Merged:
                proposal_status = PHT::Merged;
                break;
        }
        p->set_proposal_status(proposal_status);
        
        switch ( atoi(pty.c_str()) )
        {
            case PHT::TOO:
                proposal_type = PHT::TOO;
                break;
            case PHT::DDT:
                proposal_type = PHT::DDT;
                break;
            case PHT::PI:
                proposal_type = PHT::PI;
                break;
            case PHT::KeyScienceProject:
                proposal_type = PHT::KeyScienceProject;
                break;
        }
        p->set_proposal_type(proposal_type);
cout<<"proposal done\n";
        //tab_name.push_back("CoAuthors");
        CoAuthors *coa = new CoAuthors;
       
        int author_id, proposal_id, coAuthorsID;
        sql<<"select author_id, proposal_id, coAuthorsID from CoAuthors where proposal_id=:id;", use(ps[id]), 
            into(author_id), into(proposal_id), into(coAuthorsID);

        coa->set_author_id(author_id);
        //coa->set_proposal_id(proposal_id); // not necessary
        coa->set_coauthorsid(coAuthorsID);

        p->set_allocated_m_coauthors(coa);
        //tab_name.push_back("ProposalEditors");
        ProposalEditors *ped = new ProposalEditors;

cout<<"CoAuthors done\n";
        int isPI, proposalEditorsID;
        string aid;
        sql<<"select author_id, isPI, more_info, proposal_id from ProposalEditors where proposal_id=:id;", use(ps[id]), 
            into(aid), into(isPI), into(more_info), into(proposal_id);

        ped->set_author_id(aid);
        ped->set_ispi(isPI);
        if (more_info.is_initialized())
        {
            ped->set_more_info(more_info.get()); // boost
        }
        ped->set_proposal_id(proposal_id);

        p->set_allocated_m_proposaleditors(ped);
cout<<"ProposalEditors done\n";
        //tab_name.push_back("Reviews");
        Reviews *rev = new Reviews;

        string grade_rank, review_comments;
        int reviewer_id, reviewsID;
        sql<<"select grade_rank, proposal_id, review_comments, reviewer_id from Reviews where proposal_id=:id;", use(ps[id]), 
            into(grade_rank), into(proposal_id), into(review_comments), into(reviewer_id);

        rev->set_grade_rank(grade_rank);
        rev->set_proposal_id(proposal_id);
        rev->set_review_comments(review_comments);
        rev->set_reviewer_id(reviewer_id);

        p->set_allocated_m_reviews(rev);
cout<<"Reviewers done\n";
        //tab_name.push_back("ScienceGoals");
        ScienceGoals *scg = new ScienceGoals;

        double frequence;
        string ins_conf, tgt_det;
        sql<<"select frequence, instrument_configurations, more_info, target_details from ScienceGoals where proposal_id=:id;", use(ps[id]), 
            into(frequence), into(ins_conf), into(more_info), into(tgt_det);

        scg->set_frequence(frequence);
        scg->set_instrument_configurations(ins_conf);
        if (more_info.is_initialized())
        {
            scg->set_more_info(more_info.get()); //boost
        }
        scg->set_target_details(tgt_det);

        p->set_allocated_m_sciencegoals(scg);
cout<<"ScienceGoals done\n";
        //tab_name.push_back("SupportingDocuments");
        SupportingDocuments *sd = new SupportingDocuments;

        string prep, sc_j, tec_j;
        sql<<"select preprints, scientific_justification, technical_justification from SupportingDocuments where proposal_id=:id;", use(ps[id]), 
            into(prep), into(sc_j), into(tec_j);

        sd->set_preprints(prep);
        sd->set_scientific_justification(sc_j);
        sd->set_technical_justification(tec_j);

        p->set_allocated_m_supportingdocuments(sd);
cout<<"SupportingDocuments done\n";
        //tab_name.push_back("TACReviews");
        TACReviews *tr = new TACReviews;

        string com, fg;
        int tac_id;
        sql<<"select comments, final_grade, tac_id from TACReviews where proposal_id=:id;", use(ps[id]), 
            into(com), into(fg), into(tac_id);

        tr->set_comments(com);
        tr->set_final_grade(fg);
        tr->set_tac_id(tac_id);

        p->set_allocated_m_tacreviews(tr);
cout<<"TACReviews done\n";
        // Adding proposal to the list
        p_w_s.push_back(p);
    }
    
    sql.close();

    return p_w_s;
}

string getDataValue(row &r, int i)
{
    stringstream doc;
    const column_properties & props = r.get_properties(i);

    doc << props.get_name() << " ";
    switch(props.get_data_type())
    {
        case dt_string:
            doc << r.get<string>(i);
            break;
        case dt_double:
            doc << r.get<double>(i);
            break;
        case dt_integer:
            doc << r.get<int>(i);
            break;
        case dt_long_long:
            doc << r.get<long long>(i);
            break;
        case dt_unsigned_long_long:
            doc << r.get<unsigned long long>(i);
            break;
        default:
            cerr<<"ERROR: in getDataValue dt_type not recognized\n";
    }

    return doc.str();
}
    

