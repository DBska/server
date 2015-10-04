#include "connectDB.h"


//void writeToDB(vector<string> command)
string writeToDB(data_s dat)
{
    string proposal_id = "";
    // Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
    // should be put in the for(i) above.
    session sql(mysql, "db=PHT user=marco password=Marco74");
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

    tr.commit();
    sql.close();

    return proposal_id;
}


vector<Proposals *> readAllProposalsFromDB(int p_status)
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

    session sql(mysql, "db=PHT user=marco password=Marco74");

    // Extracting the total number of proposals and storing each proposal_id in
    // vector<int> p_id
    row r;
    stringstream cmd;
   p_status = 1; 
    cmd<<"select proposal_id from Proposals where proposal_status = "<<p_status<<";";
    cout<<cmd.str()<<endl;
    sql << cmd.str(), into(r);

    vector<int> ps;
    for ( size_t i=0; i != r.size(); i++ )
    {
        ps.push_back( r.get<int>(i) );
    }

    // Looping thorughout all other tables collecting data.
    /*
    for (int i=0; i<tab_name.size(); i++)
    {
       for (int id=0; id<ps.size(); id++)
       {
           cmd.str( string() );
           row r;
           cmd<<"select * from "<<tab_name[i]<<" where proposal_id=\""<<ps[id]<<"\";";
           sql << cmd.str(), into(r);
           for ( size_t i=0; i != r.size(); i++ )
           {
               string nam_val;
               nam_val = getDataValue(r,i);
               stringstream tmp;
               tmp<<nam_val;
               string name;
               string value; // value as string
               tmp>>name>>value;
           }
       }
    }*/

    for (int id=0; id<ps.size(); id++)
    {
        cout<<"Retieving proposal "<<ps[id]<<endl;
        // Proposals
        Proposals *p = new Proposals;
        string abstract;
        string more_info;
        //cmd<<"select abstract, more_info from Proposals where proposal_id="<<ps[id]<<";";
        //cmd<<"select abstract from Proposals where proposal_id=110;";
        //sql<<cmd.str(), into(abstract); //,into(more_info);
        sql<<"select abstract, more_info from Proposals where proposal_id=:id;", use(ps[id]), 
            into(abstract), into(more_info);

        p->set_proposal_id(ps[id]);
        p->set_abstract(abstract);
        p->set_more_info(more_info);

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
    

