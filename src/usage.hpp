// Author:  Bruce Allen <bdallen@nps.edu>
// Created: 2/25/2013
//
// The software provided here is released by the Naval Postgraduate
// School, an agency of the U.S. Department of Navy.  The software
// bears no warranty, either expressed or implied. NPS does not assume
// legal liability nor responsibility for a User's use of the software
// or the results of such use.
//
// Please note that within the United States, copyright protection,
// under Section 105 of the United States Code, Title 17, is not
// available for any work of the United States Government and/or for
// any works created by United States Government employees. User
// acknowledges that this software contains work which was created by
// NPS government employees and is therefore in the public domain and
// not subject to copyright.
//
// Released into the public domain on February 25, 2013 by Bruce Allen.

/**
 * \file
 * Provides usage and detailed usage for the hashdb tool.
 */

#ifndef USAGE_HPP
#define USAGE_HPP

#include <config.h>

// Standard includes
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <boost/lexical_cast.hpp>
#include <getopt.h>
#include "bloom_filter_calculator.hpp"
#include "hashdb_settings.hpp"

void usage() {
  hashdb_settings_t s;

  // print usage
  std::cout
  << "hashdb Version " << PACKAGE_VERSION  << "\n"
  << "Usage: hashdb -h | -H | -V | <command>\n"
  << "    -h, --help    print this message\n"
  << "    -H            print detailed help including usage notes and examples\n"
  << "    --Version     print version number\n"
  << "\n"
  << "The hashdb tool supports the following <command> options:\n"
  << "\n"
  << "create [<hashdb settings>]+ [<bloom filter settings>]+ <hashdb>\n"
  << "    Create a new hash database.\n"
  << "\n"
  << "    Options:\n"
  << "    Please see <hashdb settings> and <bloom filter settings> for settings\n"
  << "    and default values.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>   the file path to the new hash database to create\n"
  << "\n"
  << "import [-r <repository name>] <DFXML file> <hashdb>\n"
  << "    Import hashes from file <DFXML file> into hash database <hashdb>.\n"
  << "\n"
  << "    Options:\n"
  << "    -r, --repository=<repository name>\n"
  << "        The repository name to use for the set of hashes being imported.\n"
  << "        (default is \"repository_\" followed by the <DFXML file> path).\n"
  << "\n"
  << "    Parameters:\n"
  << "    <DFXML file>   the hash database to import hashes from\n"
  << "    <hashdb>       the hash database to insert the imported hashes into\n"
  << "\n"
  << "export <hashdb> <DFXML file>\n"
  << "    Export hashes from the <hashdb> to a <DFXML file>.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       the hash database whose hash values are to be exported\n"
  << "    <DFXML file>   the DFXML file of exported hash values\n"
  << "\n"
  << "add <source hashdb> <destination hashdb>\n"
  << "    Copies hashes from the <source hashdb> to the <destination hashdb>.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <source hashdb>       the hash database to copy hashes from\n"
  << "    <destination hashdb>  the hash database to copy hashes into\n"
  << "\n"
  << "add_multiple <source hashdb 1> <source hashdb 2> <destination hashdb>\n"
  << "    Perform a union add of <source hashdb 1> and <source hashdb 2>\n"
  << "    into the <destination hashdb>.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <source hashdb 1>     a hash database to copy hashes from\n"
  << "    <source hashdb 2>     a hash database to copy hashes from\n"
  << "    <destination hashdb>  the hash database to copy hashes into\n"
  << "\n"
  << "intersect <source hashdb 1> <source hashdb 2> <destination hashdb>\n"
  << "    Copies hashes that are common to both <source hashdb 1> and\n"
  << "    <source hashdb 2> into <destination hashdb>.\n"
  << "    Hashes match when hash values match, even if their associated\n"
  << "    source repository name and filename do not match.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <source hashdb 1>     the first of two hash databases to copy the\n"
  << "                          intersection of\n"
  << "    <source hashdb 2>     the second of two hash databases to copy the\n"
  << "                          intersection of\n"
  << "    <destination hashdb>  the hash database to copy the intersection of\n"
  << "                          hashes into\n"
  << "\n"
  << "subtract <source hashdb 1> <source hashdb 2> <destination hashdb>\n"
  << "    Copy hashes in <souce hashdb 1> and not in <source hashdb 2> into\n"
  << "    <destination hashdb>.\n"
  << "    Hashes match when hash values match, even if their associated\n"
  << "    source repository name and filename do not match.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <source hashdb 1>     the hash database containing hash values that\n"
  << "                          may be added\n"
  << "    <source hashdb 2>     the hash database indicating hash values that\n"
  << "                          are not to be added\n"
  << "    <destination hashdb>  the hash database to copy the difference of\n"
  << "                          hashes into\n"
  << "\n"
  << "deduplicate <source hashdb> <destination hashdb>\n"
  << "    Copy hall hashes in <source hashdb> to <destination hashdb> except\n"
  << "    for hashes with duplicates.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <source hashdb>       the hash database to entirely remove duplicated\n"
  << "                          hashes from\n"
  << "\n"
  << "rebuild_bloom [<bloom filter settings>]+ <hashdb>\n"
  << "    Rebuilds the bloom filters in the <hashdb> hash database based on the\n"
  << "    <bloom filter settings> provided.\n"
  << "\n"
  << "    Options:\n"
  << "    <bloom filter settings>\n"
  << "        Please see <bloom filter settings> for settings and default values.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       a hash database for which the bloom filters will be rebuilt\n"
  << "\n"
  << "server <hashdb> <socket>\n"
  << "    Starts a query server service for <hashdb> at <socket> for\n"
  << "    servicing hashdb queries.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       the hash database that the server service will use\n"
  << "    <socket>       the TCP socket to make available for clients,\n"
  << "                   for example 'tcp://localhost:14500'.\n"
  << "\n"
  << "scan <hashdb> <DFXML file>\n"
  << "    Scans the <hashdb> for hashes that match hashes in the <DFXML file>\n"
  << "    and prints out matches.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       the hash database to use as the lookup source\n"
  << "    <DFXML file>   the DFXML file containing hashes to scan for\n"
  << "\n"
  << "expand_identified_blocks <hashdb_dir> <identified_blocks.txt>\n"
  << "    Prints out source information for each hash in <identified_blocks.txt>\n"
  << "    Source information includes repository name, filename, and file offset\n"
  << "\n"
  << "get_sources <hashdb>\n"
  << "    Prints out the repository name and filename of where each hash in the\n"
  << "    <hashdb> came from.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       the hash database to print all the repository name,\n"
  << "                   filename source information for\n"
  << "\n"
  << "get_statistics <hashdb>\n"
  << "    Print out statistics about the given <hashdb> database.\n"
  << "\n"
  << "    Parameters:\n"
  << "    <hashdb>       the hash database to print statistics about\n"
  << "\n"
  << "<hashdb settings> establish the settings of a new hash database:\n"
  << "    -p, --hash_block_size=<hash block size>\n"
  << "        <hash block size>, in bytes, used to generate hashes (default " << s.hash_block_size << ")\n"
  << "\n"
  << "    -m, --max_duplicates=<maximum>\n"
  << "        <maximum> number of hash duplicates allowed, or 0 for no limit\n"
  << "        (default " << s.maximum_hash_duplicates << ")\n"
  << "\n"
  << "    -t, --storage_type=<storage type>\n"
  << "        <storage type> to use in the hash database, where <storage type>\n"
  << "        is one of: btree | hash | red-black-tree | sorted-vector\n"
  << "        (default " << s.map_type << ")\n"
  << "\n"
  << "    -a, --algorithm=<hash algorithm>\n"
  << "        <hash algorithm> in use for the hash database, where <hash algorithm>\n"
  << "        is one of: md5 | sha1 | sha256\n"
//  << "        (default " << s.map_type << ")\n"
  << "        (default md5)\n"
  << "\n"
  << "    -b, --bits=<number>\n"
  << "        <number> of source lookup index bits to use for the source lookup\n"
  << "        index, between 32 and 40 (default " << (uint32_t)s.source_lookup_index_bits << ")\n"
  << "        The number of bits used for the hash block offset value is\n"
  << "        (64 - <number>).\n"
  << "\n"
  << "<bloom filter settings> tune performance during hash queries:\n"
  << "    --bloom1 <state>\n"
  << "        sets bloom filter 1 <state> to enabled | disabled (default " << bloom_state_to_string(s.bloom1_is_used) << ")\n"
  << "    --bloom1_n <n>\n"
  << "        expected total number <n> of unique hashes (default " << bloom_filter_calculator::approximate_M_to_n(s.bloom1_M_hash_size) << ")\n"
  << "    --bloom1_kM <k:M>\n"
  << "        number of hash functions <k> and bits per hash <M> (default <k>=" << s.bloom1_k_hash_functions << "\n"
  << "        and <M>=" << s.bloom1_M_hash_size << " or <M>=value calculated from value in --b1n)\n"
  << "    --bloom2 <state>\n"
  << "        sets bloom filter 1 <state> to enabled | disabled (default " << bloom_state_to_string(s.bloom2_is_used) << ")\n"
  << "    --bloom2_n <total>\n"
  << "        expected total number <n> of unique hashes (default " << bloom_filter_calculator::approximate_M_to_n(s.bloom2_M_hash_size) << ")\n"
  << "    --bloom2_kM <k:M>\n"
  << "        number of hash functions <k> and bits per hash <M> (default <k>=" << s.bloom2_k_hash_functions << "\n"
  << "        and <M>=" << s.bloom2_M_hash_size << " or <M>=value calculated from value in --bloom2_n)\n"
  << "\n"
  ;
}

void detailed_usage() {
  hashdb_settings_t s;

  // print usage notes and examples
  std::cout
  << "\n"
  << "Notes:\n"
  << "Using the md5deep tool to generate hash data:\n"
  << "hashdb imports hashes from DFXML files that contain cryptographic\n"
  << "hashes of hash blocks.  These files can be generated using the md5deep tool\n"
  << "or by exporting a hash database using the hashdb \"export\" command.\n"
  << "When using the md5deep tool to generate hash data, the \"-p <partition size>\"\n"
  << "option must be set to the desired hash block size.  This value must match\n"
  << "the hash block size that hashdb expects or else no hashes will be\n"
  << "copied in.  The md5deep tool also requires the \"-d\" option in order to\n"
  << "instruct md5deep to generate output in DFXML format.\n"
  << "\n"
  << "Selecting an optimal hash database storage type:\n"
  << "The storage type option, \"-t\", selects the storage type to use in the\n"
  << "hash database.  Each storage type has advantages and disadvantages:\n"
  << "    btree           Provides fast build times, fast access times, and is\n"
  << "                    fairly compact.\n"
  << "                    Currently, btree may have threading issues and may\n"
  << "                    crash when performing concurrent queries.\n"
  << "\n"
  << "    hash            Provides fastest query times and is very compact,\n"
  << "                    but is very slow during building.  We recommend\n"
  << "                    building a hash database using the btree storage type,\n"
  << "                    and, once built, copying it to a new hash database\n"
  << "                    using the hash storage type option.\n"
  << "\n"
  << "    red-black-tree  Similar in performance to btree, but not as fast or\n"
  << "                    compact.\n"
  << "\n"
  << "    sorted-vector   Similar in performance to hash.\n"
  << "\n"
  << "Selecting the hash algorithm:\n"
  << "The hash alogirthm option, \"-a\", selects the algorighm in use for the hash\n"
  << "database.  Available hash algorithms are md5, sha1, and sha256.\n"
  << "\n"
  << "Improving query speed by using Bloom filters:\n"
  << "Bloom filters can speed up performance during hash queries by quickly\n"
  << "indicating if a hash value is not in the hash database.  When the Bloom\n"
  << "filter indicates that a hash value is not in the hash database, an actual\n"
  << "hash database lookup is not required, and time is saved.  If the Bloom\n"
  << "filter indicates that the hash value may be in the hash database, a hash\n"
  << "database lookup is required and no time is saved.\n"
  << "\n"
  << "Bloom filters can be large and can take up lots of disk space and memory.\n"
  << "A Bloom filter with a false positive rate between 1\% and 10\% is effictive.\n"
  << "If the false-positive rate is low, the Bloom filter is unnecessarily large,\n"
  << "and it could be smaller.  If the false-positive rate is too high, there\n"
  << "will be so many false positives that hash database lookups will be required\n"
  << "anyway, defeating the value of the bloom filter.\n"
  << "\n"
  << "Up to two Bloom filters may be used.  The idea of using two is that the\n"
  << "first would be smaller and would thus be more likely to be fully cached\n"
  << "in memory.  If the first Bloom filter indicates that the hash may be present,\n"
  << "then the second bloom filter, which should be larger, is checked.  If the\n"
  << "second Bloom filter indicates that the hash may be present, then a hash\n"
  << "database lookup is required to be sure.\n"
  << "\n"
  << "Using the bulk_extractor hashid scanner:\n"
  << "The bulk_extractor hashid scanner provides two capabilities: 1) querying\n"
  << "for blacklist hash values, and 2) populating a hash database with hash\n"
  << "values.  Options that control the hashid scanner are provided to\n"
  << "bulk_extractor using \"-S name=value\" parameters when bulk_extractor is\n"
  << "invoked.  Available options are: \n"
  << "    hashdb_path_or_socket   The server service to the hash database used must\n"
  << "                      be specified as a path or a socket, such as \"my_hashdb\"\n"
  << "                      or \"tcp://localhost:14500\".\n"
  << "\n"
  << "    hashdb_action     The action the hashid scanner will take, \"scan\"\n"
  << "                      to scan for matching hash values, or \"import\" to import\n"
  << "                      hashes into the database (default \"scan\").\n"
  << "\n"
  << "    hashdb_hash_alg   The cryptographic hash algorithm to use, \"md5\", \"sha1\",\n"
  << "                      or \"sha256\" (default \"md5\").\n"
  << "\n"
  << "    hash_block_size   The size of the hash blocks, in bytes, used to generate\n"
  << "                      cryptographic hashes (default 4096).\n"
  << "\n"
  << "    sector_size       Sector size, in bytes, for generating hashes\n"
  << "                      (default 512).\n"
  << "                      Used only in hashdb_action \"scan\".\n"
  << "\n"
  << "    repository_name   Repository name to use when importing.\n"
  << "                      Used only in hashdb_action \"import\".\n"
  << "\n"
  << "Improving startup speed by keeping a hash database open:\n"
  << "In the future, a dedicated provision may be created for this, but for now,\n"
  << "the time required to open a hash database may be avoided by keeping a\n"
  << "persistent hash database open by starting a hash database query server\n"
  << "service and keeping it running.  Now this hash database will open quickly\n"
  << "for other query services because it will already be cached in memory.\n"
  << "Caution, though, do not change the contents of a hash database that is\n"
  << "opened by multiple processes because this will make the copies inconsistent.\n"
  << "\n"
/* no, the user will only need to be aware of cryptographic hashes.
  << "Overloaded uses of the term \"hash\":\n"
  << "The term \"hash\" is overloaded and can mean any of the following:\n"
  << "   The cryptographic hash value being recorded in the hash database, such as\n"
  << "   an MD5 hash.\n"
  << "   The hash storage type, such as a B-Tree,  used for storing information in\n"
  << "   the hash database.\n"
  << "   The hash that the unordered map hash storage type uses in order to map\n"
  << "   a cryptographic hash record onto a hash storage slot.\n"
  << "   The hash that the Bloom filter uses to map onto a specific bit within\n"
  << "   the Bloom filter.\n"
  << "\n"
*/
  << "Log files:\n"
  << "Commands that create or modify a hash database produce a log file in the\n"
  << "hash database directory called \"log.xml\".  Currently, the log file is\n"
  << "replaced each time.  In the future, log entries will append to existing\n"
  << "content.\n"
  << "\n"
/* no, fixed in 0.9.1.
  << "Known bugs:\n"
  << "Performing hash queries in a threaded environment using the btree storage\n"
  << "type causes intermittent crashes.  This was observed when running the\n"
  << "bulk_extractor hashid scanner when bulk_extractor was scanning recursive\n"
  << "directories.  This bug will be addressed in a future release of boost\n"
  << "btree.\n"
  << "\n"
*/
  << "Examples:\n"
  << "This example uses the md5deep tool to generate cryptographic hashes from\n"
  << "hash blocks in a file, and is suitable for importing into a hash database\n"
  << "using the hashdb \"import\" command.  Specifically:\n"
  << "\"-p 4096\" sets the hash block partition size to 4096 bytes.\n"
  << "\"-d\" instructs the md5deep tool to produce output in DFXML format.\n"
  << "\"my_file\" specifies the file that cryptographic hashes will be generated\n"
  << "for.\n"
  << "The output of md5deep is directed to file \"my_dfxml_file\".\n"
  << "    md5deep -p 4096 -d my_file > my_dfxml_file\n"
  << "\n"
  << "This example uses the md5deep tool to generate hashes recursively under\n"
  << "subdirectories, and is suitable for importing into a hash database using\n"
  << "the hashdb \"import\" command.  Specifically:\n"
  << "\"-p 4096\" sets the hash block partition size to 4096 bytes.\n"
  << "\"-d\" instructs the md5deep tool to produce output in DFXML format.\n"
  << "\"-r mydir\" specifies that hashes will be generated recursively under\n"
  << "directory mydir.\n"
  << "The output of md5deep is directed to file \"my_dfxml_file\".\n"
  << "    md5deep -p 4096 -d -r my_dir > my_dfxml_file\n"
  << "\n"
  << "This example creates a new hash database named my_hashdb with default settings:\n"
  << "    hashdb create my_hashdb\n"
  << "\n"
  << "This example imports hashes from DFXML input file my_dfxml_file to hash\n"
  << "database my_hashdb, categorizing the hashes as sourced from repository\n"
  << "\"my repository\":\n"
  << "    hashdb import -r \"my repository\" my_dfxml_file my_hashdb\n"
  << "\n"
  << "This example exports hashes in my_hashdb to new DFXML file my_dfxml:\n"
  << "    hashdb export my_hashdb my_dfxml\n"
  << "\n"
  << "This example copies hashes from hash database my_hashdb1 to hash database\n"
  << "my_hashdb2.\n"
  << "    hashdb add my_hashdb1 my_hashdb2\n"
  << "\n"
  << "This example adds my_hashdb1 and my_hashdb2 into new hash database\n"
  << "my_hashdb3:\n"
  << "    hashdb add my_hashdb1 my_hashdb2 my_hashdb3\n"
  << "\n"
  << "This example removes hashes in my_hashdb1 from my_hashdb2:\n"
  << "    hashdb remove my_hashdb1 my_hashdb2\n"
  << "\n"
  << "This example removes all hashes in my_hashdb that appear more than once:\n"
  << "    hashdb deduplicate my_hashdb\n"
  << "\n"
  << "This example rebuilds the Bloom filters for hash database my_hashdb to\n"
  << "optimize it to work well with 50,000,000 different hash values:\n"
  << "    hashdb rebuild_bloom --b1n 50000000 my_hashdb\n"
  << "\n"
  << "This example starts hashdb as a server service for the hash database at\n"
  << "path my_hashdb at socket endpoint \"tcp://*:14500\":\n"
  << "    hashdb server my_hashdb tcp://*:14500\n"
  << "\n"
  << "This example searches the hashdb server service available at socket\n"
  << "tcp://localhost:14500 for hashes that match those in DFXML file my_dfxml\n"
  << "and directs output to stdout:\n"
  << "    hashdb query_hash tcp://localhost:14500 my_dfxml\n"
  << "\n"
  << "This example searches the hashdb server service at file path my_hashdb\n"
  << "for hashes that match those in DFXML file my_dfxml and directs output\n"
  << "to stdout:\n"
  << "    hashdb query_hash my_hashdb my_dfxml\n"
  << "\n"
  << "This example uses the hashdb server service at file path my_hashdb\n"
  << "and input file identified_blocks.txt to generate output file\n"
  << "my_identified_blocks_with_source_info.txt:\n"
  << "to stdout.\n"
  << "    hashdb get_hash_source my_hashdb identified_blocks.txt\n"
  << "    my_identified_blocks_with_source_info.txt\n"
  << "\n"
  << "This example prints out information about the hash database provided as\n"
  << "a hashdb server service at file path my_hashdb:\n"
  << "    hashdb get_hashdb_info my_hashdb\n"
  << "\n"
  << "This example uses bulk_extractor to scan for hash values in media image\n"
  << "my_image that match hashes in hash database my_hashdb, creating output in\n"
  << "feature file my_scan/identified_blocks.txt:\n"
  << "    bulk_extractor -S path_or_socket=my_hashdb -o my_scan my_image\n"
  << "\n"
  << "This example uses bulk_extractor to import hash values from media image\n"
  << "my_image into hash database my_hashdb, creating irrelavent scanner output in\n"
  << "directory my_scan:\n"
  << "    bulk_extractor -S path_or_socket=my_hashdb -S hashdb_action=import\n"
  << "    -o my_scan my_image\n"
  << "\n"
  << "This example creates new hash database my_hashdb using various tuning\n"
  << "parameters.  Specifically:\n"
  << "\"-p 512\" specifies that the hash database will contain hashes for data\n"
  << "hashed with a hash block size of 512 bytes.\n"
  << "\"-m 2\" specifies that when there are duplicate hashes, only the first\n"
  << "two hashes of a duplicate hash value will be copied.\n"
  << "\"-t hash\" specifies that hashes will be recorded using the \"hash\" storage\n"
  << "type algorithm.\n"
  << "\"-a sha1\" specifies that SHA1 hashes will be stored in the hash database.\n"
  << "type algorithm.\n"
  << "\"-b 34\" specifies that 34 bits are allocated for the source lookup index,\n"
  << "allowing 2^34 entries of source lookup data.  Note that this leaves 2^30\n"
  << "entries remaining for hash block offset values.\n"
  << "\"--bloom1 enabled\" specifies that Bloom filter 1 is enabled.\n"
  << "\"--bloom1_n 50000000\" specifies that Bloom filter 1 should be sized to expect\n"
  << "50,000,000 different hash values.\n"
  << "\"--bloom2 enabled\" specifies that Bloom filter 2 is enabled.\n"
  << "\"--bloom2_kM 4:32 enabled\" specifies that Bloom filter 2 will be configured to\n"
  << "have 4 hash functions and that the Bloom filter hash function size will be\n"
  << "32 bits, consuming 512MiB of disk space.\n"
  << "    hashdb create -p 512 -m 2 -t hash -a sha1 -b 34 --bloom1 enabled\n"
  << "    --bloom1_n 50000000 --bloom2 enabled --bloom2_kM 4:32 my_hashdb1 my_hashdb2\n"
  ;
}

#endif

