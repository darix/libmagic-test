# libmagic-test

I really wonder if this is a valid use case, but atm it fails with:

```
Error in magic_buffer(): no magic files loaded
```

A potential fix is this patch from the charlock_holmes project:

```
--- src/funcs.c.orig    2013-01-27 01:23:01.000000000 -0800
+++ src/funcs.c 2013-01-27 01:23:46.000000000 -0800
@@ -300,7 +300,7 @@
 protected int
 file_reset(struct magic_set *ms)
 {
-       if (ms->mlist == NULL) {
+       if (!(ms->flags & MAGIC_NO_CHECK_SOFT) &&  ms->mlist == NULL) {
                file_error(ms, 0, "no magic files loaded");
                return -1;
        }
```