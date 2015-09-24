#include "connectDB.h"


//void writeToDB(vector<string> command)
string writeToDB(data_s dat)
{
    string proposal_id = "";
    // Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
    // should be put in the for(i) above.
    session sql(mysql, "db=PHT user=marco password=Marco74");

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
    else // a modification is requested.
    {
        // The proposal_id is available inside the message.
        int nf = dat.name[0].size();
        for (int i=0; i<nf; i++)
        {
            if ( dat.name[0][i] == "proposal_id" )
                proposal_id = dat.value[0][i];
        }
        cout<<"Arrived a request for proposal_id "<<proposal_id<<endl;

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

    return proposal_id;
}


void readFromDB()
{



}
