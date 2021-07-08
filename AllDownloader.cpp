/**********************************************************/
/*                   Jorge M. Robles                      */
/*           All Downloader - A image downloader          */
/**********************************************************/

/**********************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <urlmon.h>

#pragma comment(lib, "Urlmon.lib")

using namespace std;

/**********************************************************/



string image; //this is the return of the url of searchimages()
int iterator_name = 0; //the name of the image 


/**********************************************************/

int main()
{
    //A link of a manga web in a char array, please
    char link[100];

    cout << "Hi, welcome to AllDownloader, your console app to download manga in JPG/PNG format." << endl;
    cout << "Please, put the link whose manga you want to download" << endl;
    cin.get(link, 100);
    cout << "Are you sure do you want to download from this web?\n" << link << endl;

    //Is a char array?
    cout << typeid(link).name() << endl;

    // Is this a link? Comparing the beginning of a good url to my url
    int value_begin;
    int value2_begin;

    value_begin = 0;
    value2_begin = 0;
    char link_begin[] = "https://";
    char link2_begin[] = "http://";

    for (int i = 0; i < 8; i++)
    {
        if (link[i] == link_begin[i])
        {
            value_begin++;
            cout << "First possible value:" << value_begin << "/8" << endl;
        }

        if (link[i] == link2_begin[i])
        {
            value2_begin++;
            cout << "Second possible value:" << value2_begin << "/7" << endl;
        }
    }

    if (value_begin == 8 || value2_begin == 7)
    {
        cout << "It's a link" << endl;

        //functions for that link
        string url;
        url = link;
        int openandsavelink(string linkarg); //create and invoke the function to obtain the data from the link
        int readmyfile(); //read that data
        string searchimages(); //search images from the read data
        int rewritestring(string imagestring); //rewrite the text file deleting the last search 
        int getimages(string imagestring); //get these images
        void goto_nextimage(); //jump between urls until there's no match

        openandsavelink(url);
        readmyfile();
        string imagestr = searchimages();
        goto_nextimage();
    }
    else
    {
        cout << value_begin << endl;
        cout << "It'snt a link" << endl;
        return -1;
    }

    return 0;
}

int openandsavelink(string linkarg)
{
    // Program to download the url's page to a file named myfile.txt
    // The file's created in the same working directory 

    //convert parameter to wstring and then get the C string  
    string str = linkarg;
    wstring widestr = wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();

    // the URL to download from
    const wchar_t* srcURL = widecstr;

    // the destination file 
    const wchar_t* destFile = L"myfile.txt";

    // URLDownloadToFile returns S_OK on success 
    if (S_OK == URLDownloadToFile(NULL, srcURL, destFile, 0, NULL))
    {
        printf("Saved to 'myfile.txt'");
        return 0;
    }
    else
    {
        printf("Failed");
        return -1;
    }

}

int readmyfile()
{
    //Read all the data from myfile.txt 

    fstream newfile;

    newfile.open("myfile.txt", ios::in);

    if (newfile.is_open()) {
        string datafile;

        //read the data put it into string.
        while (getline(newfile, datafile)) {
            cout << datafile << "\n";
        }

        newfile.close();
    }
    return 0;
}

string searchimages()
{
    //If there's a match in myfile.txt, it's shown

    string strimage_begin, strimage_end;
    string strimage2_begin, strimage2_end;
    string datafile;
    ifstream inFile;

    strimage_begin = "https://";
    strimage_end = ".jpg";
    strimage2_begin = "http://";
    strimage2_end = ".png";

    inFile.open("myfile.txt");

    if (!inFile)
    {
        exit(1);
    }

    while (inFile.good())
    {
        getline(inFile, datafile);

        size_t pos_begin = datafile.find(strimage_begin);
        size_t pos_end = datafile.find(strimage_end);
        size_t pos2_begin = datafile.find(strimage2_begin);
        size_t pos2_end = datafile.find(strimage2_end);

        if (pos_begin != string::npos && pos_end != string::npos)
        {
            cout << "Found" << endl;

            //we need to "substring" the line (string) found in order to identify 
            //the length we want it (total's length - end's length => url's beginning&ending)     
            int sublen, sub2len;
            int substrings;

            string sub = datafile.substr(pos_begin);
            string sub2 = datafile.substr(pos_end);

            sublen = 0;
            sub2len = 0;
            sublen = sub.length();
            sub2len = sub2.length();
            substrings = sublen - sub2len;
            cout << "String found is: " << sub << " and their length: " << sublen << " and " << sub2len << endl;
            cout << "And the other part: " << substrings << endl;

            //the image url is shorted until its extension. The other we don't want it 
            sub.resize(substrings + 4);
            string imageurl = sub;
            cout << "The image url is: " << imageurl << endl;
            image = imageurl;
            break;
        }

        if (pos2_begin != string::npos && pos_end != string::npos)
        {
            cout << "Found" << endl;

            //we need to "substring" the line (string) found in order to identify 
            //the length we want it (total's length - end's length => url's beginning&ending)     
            int sublen, sub2len;
            int substrings;

            string sub = datafile.substr(pos2_begin);
            string sub2 = datafile.substr(pos_end);

            sublen = 0;
            sub2len = 0;
            sublen = sub.length();
            sub2len = sub2.length();
            substrings = sublen - sub2len;
            cout << "String found is: " << sub << " and their length: " << sublen << " and " << sub2len << endl;
            cout << "And the other part: " << substrings << endl;

            //the image url is shorted until its extension. The other we don't want it 
            sub.resize(substrings + 4);
            string imageurl = sub;
            cout << "The image url is: " << imageurl << endl;
            image = imageurl;
            break;
        }

        if (pos_begin != string::npos && pos2_end != string::npos)
        {
            cout << "Found" << endl;

            //we need to "substring" the line (string) found in order to identify 
            //the length we want it (total's length - end's length => url's beginning&ending)     
            int sublen, sub2len;
            int substrings;

            string sub = datafile.substr(pos_begin);
            string sub2 = datafile.substr(pos2_end);

            sublen = 0;
            sub2len = 0;
            sublen = sub.length();
            sub2len = sub2.length();
            substrings = sublen - sub2len;
            cout << "String found is: " << sub << " and their length: " << sublen << " and " << sub2len << endl;
            cout << "And the other part: " << substrings << endl;

            //the image url is shorted until its extension. The other we don't want it 
            sub.resize(substrings + 4);
            string imageurl = sub;
            cout << "The image url is: " << imageurl << endl;
            image = imageurl;
            break;
        }

        if (pos2_begin != string::npos && pos2_end != string::npos)
        {
            cout << "Found" << endl;

            //we need to "substring" the line (string) found in order to identify 
            //the length we want it (total's length - end's length => url's beginning&ending)     
            int sublen, sub2len;
            int substrings;

            string sub = datafile.substr(pos2_begin);
            string sub2 = datafile.substr(pos2_end);

            sublen = 0;
            sub2len = 0;
            sublen = sub.length();
            sub2len = sub2.length();
            substrings = sublen - sub2len;
            cout << "String found is: " << sub << " and their length: " << sublen << " and " << sub2len << endl;
            cout << "And the other part: " << substrings << endl;

            //the image url is shorted until its extension. The other we don't want it 
            sub.resize(substrings + 4);
            string imageurl = sub;
            cout << "The image url is: " << imageurl << endl;
            image = imageurl;
            break;
        }
    }

    return image;
}

int rewritestring(string imagestring)
{
    //Rewrite myfile.txt creating a copy without the last image saved and erasing the original file

    string line;
    string eraseline = imagestring;
    ifstream fin;
    string path = "myfile.txt";

    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
        while (true)
        {
            size_t len = eraseline.length();
            size_t pos = line.find(eraseline);
            if (pos != string::npos)
            {
                line.replace(pos, len, "");
            }
            else
            {
                break;
            }
        }
        temp << line << '\n';
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char* p = path.c_str();
    remove(p);
    rename("temp.txt", p);

    return 0;
}

int getimages(string imagestring)
{
    //Download the image from the given url

    //each image is saved with a different name with a number
    iterator_name++;
    string url = imagestring;
    size_t len = url.length();
    wstring iterator_namewstr = to_wstring(iterator_name);
    LPCWSTR iterator_namecstr = iterator_namewstr.c_str();
    LPCWSTR download_filebegin = L"C:\\Users\\jocar\\source\\repos\\App2\\";
    LPCWSTR download_fileend = L".jpg";
    wstring download_file = wstring(download_filebegin) + iterator_namecstr + download_fileend;
    LPCWSTR downloadfile_complete = download_file.c_str();

    int nmlen = MultiByteToWideChar(CP_ACP, 0, url.c_str(), len + 1, NULL, 0);//if the function runs successfully and cchWideChar is zero,
    //the return value is the number of wide characters required by the buffer receiving the string to be converted.
    wchar_t* buffer = new wchar_t[nmlen];

    MultiByteToWideChar(CP_ACP, 0, url.c_str(), len + 1, buffer, nmlen);
    HRESULT hr = URLDownloadToFile(NULL, buffer, downloadfile_complete, 0, NULL);

    if (hr == S_OK)
    {
        cout << "Download successful" << endl;
    }
    else
    {
        cerr << "Error downloading" << endl;
    }

    return 0;
}

void goto_nextimage()
{
    //Jump between the images until end of matching 

    const string lastimage = image;
    string nextimage;
    int i = 0;

    //only the first time executing 
    if (i == 0)
    {
        rewritestring(lastimage);
        getimages(lastimage);
        i++;
    }

    //until there's no more url images to download
    while (lastimage != nextimage)
    {
        string imagestr = searchimages();

        if (nextimage == imagestr)
        {
            break;
        }

        rewritestring(imagestr);
        getimages(imagestr);
        nextimage = imagestr;
    }

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración