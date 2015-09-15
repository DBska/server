#include "connectDB.h"


void writeToDB(vector<string> command)
{
    // Inserting the data into the DB with SOCI. I know it is only ONE data. The following part of the code
    // should be put in the for(i) above.
    session sql(mysql, "db=PHT user=marco password=Marco74");

    // before inserting, printing the currente number of Proposals
    int count;
    sql<<"select count(*) from Proposals", into(count);
    cout<<"Table Proposals has "<<count<<" entries"<<endl;

    // Inserting the data
    //sql<<"insert into Proposals (abstract) values(:abstractp)", use(proposal.abstract());
    for (int i=0; i<command.size(); i++)
    {
        sql<<command[i];
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
        cout << r <<") " << "Id: " << row.get<int>(0)
             << " Abstract: " << row.get<string>(1)  << endl;
        r++;
    }
}


void readFromDB()
{



}
