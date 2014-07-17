Require Import floyd.proofauto.
Require Import sha.sha.
Require Import sha.SHA256.
Require Import sha.spec_sha.
Require Import sha.sha_lemmas.
Require Import sha.verif_sha_final2.
Require Import sha.verif_sha_final3.
Local Open Scope logic.

Lemma body_SHA256_Final: semax_body Vprog Gtot f_SHA256_Final SHA256_Final_spec.
Proof.
start_function.
name md_ _md.
name c_ _c.
name p _p.
name n _n.
name cNl _cNl.
name cNh _cNh.
unfold sha256state_; normalize.
intros [r_h [r_Nl [r_Nh [r_data r_num]]]].
simpl_data_at.
normalize.
unfold s256_relate in H0.
unfold s256_h, s256_Nh,s256_Nl, s256_num, s256_data, fst,snd in H0|-*.
destruct a as [hashed data].
destruct H0 as [H0 [H1 [H2 [[H3 DDbytes] [H4 H5]]]]].
destruct H1 as [hi [lo [? [? ?]]]].
subst r_Nh r_Nl r_num r_data. rename data into dd.
assert (H3': (Zlength dd < 64)%Z) by assumption.
unfold at_offset.
forward. (* p = c->data;  *)
entailer!.
forward. (* n = c->num; *)
simpl.
unfold at_offset.  (* maybe this line should not be necessary *)
forward. (* p[n] = 0x80; *)
entailer!. rewrite Zlength_correct in H3'|-*; omega.
forward. (* n++; *)
rewrite upd_Znth_next
  by (repeat rewrite initial_world.Zlength_map; auto).
simpl. normalize. 
subst r_h. simpl.
change (Int.zero_ext 8 (Int.repr 128)) with (Int.repr 128).
change (align 40 1)%Z with 40%Z.
set (ddlen :=  Zlength dd).
assert (Hddlen: (0 <= ddlen < 64)%Z).
unfold ddlen. split; auto. rewrite Zlength_correct; omega.
repeat rewrite  initial_world.Zlength_map.
forward_if   (invariant_after_if1 hashed dd c md shmd  hi lo).
* (* then-clause *)
 change Delta with Delta_final_if1.
match goal with |- semax _ _ ?c _ => change c with Body_final_if1 end.
 simpl typeof.
unfold POSTCONDITION, abbreviate; clear POSTCONDITION.
 make_sequential. rewrite overridePost_normal'.
unfold ddlen in *; clear ddlen.
apply (ifbody_final_if1 Espec hashed md c shmd hi lo dd H4 H7 H3 DDbytes).
* (* else-clause *)
forward. (* skip; *)
unfold invariant_after_if1.
normalize. rewrite overridePost_normal'. 
apply exp_right with hashed.
apply exp_right with (dd ++ [128]).
apply exp_right with 0%Z.
entailer.
rewrite mul_repr, sub_repr in H1; apply ltu_repr_false in H1.
2: split; computable.
2: assert (64 < Int.max_unsigned)%Z by computable; unfold ddlen in *;
   split; try omega.
clear TC0.
change (16*4)%Z with (Z.of_nat CBLOCK) in H1.
apply andp_right; [apply prop_right; repeat split | cancel].
rewrite Forall_app; split; auto.
repeat constructor; omega.
rewrite app_length; simpl. apply Nat2Z.inj_ge.
repeat rewrite Nat2Z.inj_add; unfold ddlen in H1; rewrite Zlength_correct in H1.
change (Z.of_nat 1) with 1%Z; change (Z.of_nat 8) with 8%Z.
omega.
f_equal. unfold ddlen; repeat rewrite Zlength_correct; f_equal.
rewrite app_length; simpl. rewrite Nat2Z.inj_add; reflexivity.
repeat rewrite map_app; apply derives_refl.
* unfold invariant_after_if1.
apply extract_exists_pre; intro hashed'.
apply extract_exists_pre; intro dd'.
apply extract_exists_pre; intro pad.
apply semax_extract_PROP; intro DDbytes'.
apply semax_extract_PROP; intro PAD.
normalize.
unfold POSTCONDITION, abbreviate; clear POSTCONDITION.
unfold sha_finish.
unfold SHA_256.
clear ddlen Hddlen.

forward_call (* memset (p+n,0,SHA_CBLOCK-8-n); *)
  (Tsh,
     offset_val (Int.repr (Zlength dd')) (offset_val (Int.repr 40) c)%Z, 
     (Z.of_nat CBLOCK - 8 - Zlength dd')%Z,
     Int.zero).
change 40%Z with data_offset.
entailer!.
rewrite Int.unsigned_repr. Omega1. Omega1. 
rewrite (split_array_at (Zlength dd') tuchar).
rewrite (split_array_at (Z.of_nat CBLOCK - 8)%Z tuchar _ _ _ 64%Z).
repeat rewrite <- sepcon_assoc.
pull_left (array_at tuchar Tsh (ZnthV tuchar (map Vint (map Int.repr dd'))) (Zlength dd') (Z.of_nat CBLOCK - 8)%Z
   (offset_val (Int.repr data_offset) c)).
repeat rewrite sepcon_assoc; apply sepcon_derives; [ | cancel].
replace (offset_val (Int.repr (data_offset + Zlength dd')) c)%Z
    with (offset_val (Int.repr (sizeof tuchar * Zlength dd')) (offset_val (Int.repr 40) c))%Z.
destruct (zlt 0 (Z.of_nat CBLOCK - 8 - Zlength dd')).
Focus 2. {
  assert (Z.of_nat CBLOCK - 8 - Zlength dd' = 0)%Z.
    clear - g H0. apply Nat2Z.inj_le in H0. rewrite Nat2Z.inj_add in H0.
 change (Z.of_nat 8) with 8 in H0; rewrite <- Zlength_correct in H0.
  omega. 
 rewrite H8. replace (Z.of_nat CBLOCK - 8) with (Zlength dd') by omega.
 rewrite array_at_emp. 
 destruct c; try (contradiction Pc).
 simpl; rewrite memory_block_zero.
 apply andp_left2; auto.
} Unfocus.
   replace (Z.of_nat CBLOCK - 8 - Zlength dd')%Z
     with (sizeof (tarray tuchar (Z.of_nat CBLOCK - 8 - Zlength dd')))%Z
    by (apply sizeof_tarray_tuchar; omega).
 rewrite memory_block_typed.
  simpl_data_at.
   rewrite <- offset_val_array_at.
 rewrite Z.add_0_r.
 apply derives_refl'; apply equal_f.
 replace (Zlength dd' + (Z.of_nat CBLOCK - 8 - Zlength dd'))%Z
  with (Z.of_nat CBLOCK - 8)%Z by (clear; omega).
 apply array_at_ext; intros.
 unfold ZnthV.
  rewrite if_false
  by (clear - H8; destruct H8 as [H8 _]; rewrite Zlength_correct in H8; omega).
  rewrite if_false by omega.
rewrite nth_overflow
 by (rewrite map_map, map_length;
     clear - H8; destruct H8 as [H8 _]; rewrite Zlength_correct in H8;
     rewrite <- (Z2Nat.id i) in H8 by omega; 
     apply Nat2Z.inj_le; auto).
  rewrite nth_overflow by (clear; simpl length; omega).
  reflexivity.
  reflexivity.
  change (sizeof tuchar) with 1%Z; rewrite Z.mul_1_l.
  rewrite offset_offset_val. rewrite add_repr; auto.
  clear - H0. apply Nat2Z.inj_le in H0. rewrite Nat2Z.inj_add in H0.
  rewrite Zlength_correct; change (Z.of_nat CBLOCK) with 64 in *;
  change (Z.of_nat 8) with 8 in H0; omega.
  clear - H0. apply Nat2Z.inj_le in H0. rewrite Nat2Z.inj_add in H0.
  rewrite Zlength_correct; change (Z.of_nat CBLOCK) with 64 in *;
  change (Z.of_nat 8) with 8 in H0; omega.
  cbv beta iota. autorewrite with subst.
replace_SEP 0%Z (`(array_at tuchar Tsh (fun _ : Z => Vint Int.zero) 0
          (Z.of_nat CBLOCK - 8 - Zlength dd')
          (offset_val (Int.repr (Zlength dd')) (offset_val (Int.repr 40) c)))).
entailer!.
 forward.  (* p += SHA_CBLOCK-8; *)
 entailer!.
 simpl eval_binop. normalize.
 unfold force_val2. simpl force_val. rewrite mul_repr, sub_repr.

 replace Delta with Delta_final_if1
  by (simplify_Delta; reflexivity).
unfold POSTCONDITION, abbreviate; clear POSTCONDITION.
simple apply final_part2 with pad; assumption.
Qed.
