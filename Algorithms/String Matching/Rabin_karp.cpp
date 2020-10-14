/*Rolling Hash
1) Calculate Hash for pattern
2) Calculate Hash for 1st window in text
3) Repeat the following : (until text ends)
	a) If Hash(pat)==Hash(Text_Window)
	then match characters one by one
	b) Subtract leftmost (msb) from HASH(text_window)
 	c) Shift entire hash(text_window) by 1 unit to left
	d) Add new character to window
*/

#include<bits/stdc++.h>
#define ll long long int
using namespace std;

ll createHashValue (string text, int len, ll prime) {

    ll result = 0;
    for (int i=0; i<len; i++) {
      result += (ll)text[i]*(ll)pow(prime,i);
    }

    return result;
}

ll reCalculateHash (string str, int oldIndex, int newIndex, ll oldHash, int patLen, ll prime) {
  ll newhash = oldHash - str[oldIndex];
  newhash=newhash/prime;
  newhash+= (ll)str[newIndex]*(ll)pow(prime, patLen-1);
  return newhash;
}

bool checkEqual (string str1, string str2, int start1, int end1, int start2, int end2) {

    if(end1-start1!=end2-start2)
      return false;

    while (start1<=end1 && start2<=end2) {
      if(str1[start1]!=str2[start2])
        return false;
      start1++;
      start2++;
    }
    return true;
}


void solve(){

  string str = "ababcabdabd";
  string pat  = "abd";
  ll prime = 119;

  ll patHash = createHashValue(pat,pat.length(),prime);
  ll strHash = createHashValue(str,pat.length(),prime);

  for (int i=0; i<=str.length()-pat.length(); i++) {
    if (patHash == strHash && checkEqual(str,pat,i,i+pat.length()-1,0,pat.length()-1)){
      // found pattern at index i
      cout<<i<<endl;
      return ;
    }

    if (i<str.length()-pat.length()) {
      strHash = reCalculateHash(str, i, i+pat.length(), strHash, pat.length(), prime);
    }

  }

}

int main() {
   solve();
   return 0;
}
