#ifndef COLOR_H
# define COLOR_H

/*
 *Regular text
 */

# define BLK "\001\e[0;30m\002"
# define RED "\001\e[0;31m\002"
# define GRN "\001\e[0;32m\002"
# define YEL "\001\e[0;33m\002"
# define BLU "\001\e[0;34m\002"
# define MAG "\001\e[0;35m\002"
# define CYN "\001\e[0;36m\002"
# define WHT "\001\e[0;37m\002"

/*
 *Regular bold text
 */

# define BBLK "\001\e[1;30m\002"
# define BRED "\001\e[1;31m\002"
# define BGRN "\001\e[1;32m\002"
# define BYEL "\001\e[1;33m\002"
# define BBLU "\001\e[1;34m\002"
# define BMAG "\001\e[1;35m\002"
# define BCYN "\001\e[1;36m\002"
# define BWHT "\001\e[1;37m\002"

/*
 *Regular underlined text
 */

# define UBLK "\001\e[4;30m\002"
# define URED "\001\e[4;31m\002"
# define UGRN "\001\e[4;32m\002"
# define UYEL "\001\e[4;33m\002"
# define UBLU "\001\e[4;34m\002"
# define UMAG "\001\e[4;35m\002"
# define UCYN "\001\e[4;36m\002"
# define UWHT "\001\e[4;37m\002"

/*
 *Regular background text
 */

# define BLKB "\001\e[40m\002"
# define REDB "\001\e[41m\002"
# define GRNB "\001\e[42m\002"
# define YELB "\001\e[43m\002"
# define BLUB "\001\e[44m\002"
# define MAGB "\001\e[45m\002"
# define CYNB "\001\e[46m\002"
# define WHTB "\001\e[47m\002"

/*
 *High intensty background 
 */

# define BLKHB "\001\e[0;100m\002"
# define REDHB "\001\e[0;101m\002"
# define GRNHB "\001\e[0;102m\002"
# define YELHB "\001\e[0;103m\002"
# define BLUHB "\001\e[0;104m\002"
# define MAGHB "\001\e[0;105m\002"
# define CYNHB "\001\e[0;106m\002"
# define WHTHB "\001\e[0;107m\002"

/*
 *High intensty text
 */

# define HBLK "\001\e[0;90m\002"
# define HRED "\001\e[0;91m\002"
# define HGRN "\001\e[0;92m\002"
# define HYEL "\001\e[0;93m\002"
# define HBLU "\001\e[0;94m\002"
# define HMAG "\001\e[0;95m\002"
# define HCYN "\001\e[0;96m\002"
# define HWHT "\001\e[0;97m\002"

/*
 *Bold high intensity text
 */

# define BHBLK "\001\e[1;90m\002"
# define BHRED "\001\e[1;91m\002"
# define BHGRN "\001\e[1;92m\002"
# define BHYEL "\001\e[1;93m\002"
# define BHBLU "\001\e[1;94m\002"
# define BHMAG "\001\e[1;95m\002"
# define BHCYN "\001\e[1;96m\002"
# define BHWHT "\001\e[1;97m\002"

/*
 *Reset
 */

# define RESET "\001\e[0m\002"

#endif
