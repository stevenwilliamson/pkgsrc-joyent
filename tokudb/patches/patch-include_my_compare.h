$NetBSD: patch-include_my_compare.h,v 1.1 2011/05/07 04:03:08 adam Exp $

Adjust HA_MAX_KEY_LENGTH x4.

--- include/my_compare.h.orig	2015-01-21 20:49:23.000000000 +0000
+++ include/my_compare.h
@@ -39,7 +39,7 @@ extern "C" {
   But beware the dependency of MI_MAX_POSSIBLE_KEY_BUFF and HA_MAX_KEY_LENGTH.
 */
 
-#define HA_MAX_KEY_LENGTH           1000        /* Max length in bytes */
+#define HA_MAX_KEY_LENGTH           4000        /* Max length in bytes */
 #define HA_MAX_KEY_SEG              16          /* Max segments for key */
 
 #define HA_MAX_POSSIBLE_KEY_BUFF    (HA_MAX_KEY_LENGTH + 24+ 6+6)
