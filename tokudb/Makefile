# $NetBSD$

DISTNAME=	mysql-5.5-${TKNAME}
PKGNAME=	mysql55-${TKNAME}
CATEGORIES=	databases
MASTER_SITES=	https://github.com/Tokutek/mysql-5.5/archive/
EXTRACT_SUFX=	.tar.gz

MAINTAINER=	filip@joyent.com
HOMEPAGE=	http://www.tokutek.com/
COMMENT=	High-performance storage engine for MySQL
#LICENSE=	# TODO: (see mk/license.mk)

TKNAME=		tokudb-7.5.6
TKFILES=	tokudb-backup-plugin ft-index jemalloc mysql-5.5 tokudb-engine

.include "../../joyent/tokudb/Makefile.common"

DIST_SUBDIR=	tokudb

.for file in ${TKFILES}
DISTFILES+=				${file}-${TKNAME}${EXTRACT_SUFX}
SITES.${file}-${TKNAME}${EXTRACT_SUFX}=	-http://github.com/Tokutek/${file}/archive/${TKNAME}${EXTRACT_SUFX}
.endfor

WRKSRC=		${WRKDIR}/mysql-5.5-${TKNAME}
USE_CMAKE=	yes
USE_LANGUAGES=	c c++
USE_TOOLS+=	yacc pax

CHECK_PORTABILITY_SKIP+=	extra/jemalloc/configure	\
				storage/tokudb/ft-index/third_party/jemalloc/configure

CMAKE_ARGS+=	-DBUILD_CONFIG=mysql_release
CMAKE_ARGS+=	-DBUILD_TESTING=OFF
CMAKE_ARGS+=	-DCMAKE_BUILD_TYPE=RelWithDebInfo
CMAKE_ARGS+=	-DMYSQL_MAINTAINER_MODE=OFF
CMAKE_ARGS+=	-DTOKUDB_VERSION=${TKNAME}
CMAKE_ARGS+=	-DTOKU_DEBUG_PARANOID=OFF
CMAKE_ARGS+=	-DUSE_CSCOPE=OFF
CMAKE_ARGS+=	-DUSE_CTAGS=OFF
CMAKE_ARGS+=	-DUSE_ETAGS=OFF
CMAKE_ARGS+=	-DUSE_GTAGS=OFF
CMAKE_ARGS+=	-DUSE_VALGRIND=OFF
CMAKE_ARGS+=	-DWITH_JEMALLOC=bundled
CMAKE_ARGS+=	-DWITH_TOKUDB=ON
CMAKE_ARGS+=	-DWITH_TOKUDB_STORAGE_ENGINE=ON

BUILDLINK_TRANSFORM+=	rm:-flto 
BUILDLINK_TRANSFORM+=	rm:-fuse-linker-plugin

SUBST_CLASSES+=		ver
SUBST_STAGE.ver=	pre-configure
SUBST_MESSAGE.ver=	Preparing build
SUBST_FILES.ver=	VERSION
SUBST_SED.ver=		-e '/MYSQL_VERSION_EXTRA/s/=/=-tokudb-${PKGVERSION_NOREV}/'

# This should not be needed
#SUBST_CLASSES+=		jem
#SUBST_STAGE.jem=	pre-build
#SUBST_FILES.jem=	sql/CMakeLists.txt
#SUBST_SED.jem=		-e 's,jemalloc,-L../extra/jemalloc/lib jemalloc,'

pre-patch:
	cp -Rp ${WRKDIR}/tokudb-engine-${TKNAME}/storage/tokudb ${WRKSRC}/storage/tokudb
	cp -Rp ${WRKDIR}/ft-index-${TKNAME} ${WRKSRC}/storage/tokudb/ft-index
	cp -Rp ${WRKDIR}/jemalloc-${TKNAME} ${WRKSRC}/storage/tokudb/ft-index/third_party/jemalloc
	cp -Rp ${WRKDIR}/tokudb-backup-plugin-${TKNAME} ${WRKSRC}/plugin/tokudb-backup-plugin
	cd ${WRKDIR}/tokudb-engine-${TKNAME}/scripts && ${PAX} -rw -pp * ${WRKSRC}/scripts
	cd ${WRKDIR}/tokudb-engine-${TKNAME}/mysql-test && ${PAX} -rw -pp * ${WRKSRC}/mysql-test

.include "../../mk/bsd.pkg.mk"
