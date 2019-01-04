use strict;
use warnings;


my $directory = $ARGV[0];
opendir(DIR,$directory);

while(my $file = readdir(DIR)){
    if(-f "$directory/$file"){
        (my $filenoext = $file) =~ s/\.[^.]+$//;
        print("converting $directory/$file to farbfeld...\n");
        my $out = `2ff < $directory/$file > $directory/$filenoext.ff`;
    }
}
closedir(DIR);