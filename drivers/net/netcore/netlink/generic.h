/*++

Copyright (c) 2016 Minoca Corp. All Rights Reserved

Module Name:

    generic.h

Abstract:

    This header contains definitions for the generic netlink protocol.

Author:

    Chris Stevens 10-Feb-2016

--*/

//
// ------------------------------------------------------------------- Includes
//

//
// ---------------------------------------------------------------- Definitions
//

#define NETLINK_GENERIC_ALLOCATION_TAG 0x65676C4E // 'eglN'

//
// ------------------------------------------------------ Data Type Definitions
//

/*++

Structure Description:

    This structure defines a generic netlink family.

Members:

    TreeNode - Stores a node in the global tree of generic netlink families.

    ReferenceCount - Stores the number of references take on the family.

    MulticastGroupOffset - Stores the offset into the entire generic netlink
        multicast group ID namespace where this family's multicast group IDs
        begin.

    Properties - Stores the generic netlink family properties, including its ID
        name, and interface.

--*/

struct _NETLINK_GENERIC_FAMILY {
    RED_BLACK_TREE_NODE TreeNode;
    volatile ULONG ReferenceCount;
    ULONG MulticastGroupOffset;
    NETLINK_GENERIC_FAMILY_PROPERTIES Properties;
};

//
// -------------------------------------------------------------------- Globals
//

//
// Store the lock and tree for storing the generic netlink families.
//

extern PSHARED_EXCLUSIVE_LOCK NetNetlinkGenericFamilyLock;
extern RED_BLACK_TREE NetNetlinkGenericFamilyTree;

//
// -------------------------------------------------------- Function Prototypes
//

VOID
NetpNetlinkGenericControlInitialize (
    VOID
    );

/*++

Routine Description:

    This routine initializes the built in generic netlink control family.

Arguments:

    None.

Return Value:

    None.

--*/

KSTATUS
NetpNetlinkGenericControlSendNotification (
    PNET_SOCKET Socket,
    UCHAR Command,
    PNETLINK_GENERIC_FAMILY Family,
    PNETLINK_GENERIC_MULTICAST_GROUP Group,
    ULONG GroupId
    );

/*++

Routine Description:

    This routine sends a generic netlink control command based on the family
    and or group information.

Arguments:

    Socket - Supplies a pointer to the network socket on which to send the
        command.

    Family - Supplies a pointer to the generic netlink family for which the
        command is being sent.

    Parameters - Supplies a pointer to the command parameters.

    Group - Supplies an optional pointers to the multicast group that has
        just arrived or is being deleted.

    GroupId - Supplies an optional ID of the multicast group that has just
        arrived or is being deleted.

Return Value:

    Status code.

--*/

PNETLINK_GENERIC_FAMILY
NetpNetlinkGenericLookupFamilyById (
    ULONG FamilyId
    );

/*++

Routine Description:

    This routine searches the database of registered generic netlink families
    for one with the given ID. If successful, the family is returned with an
    added reference which the caller must release.

Arguments:

    FamilyId - Supplies the ID of the desired family.

Return Value:

    Returns a pointer to the generic netlink family on success or NULL on
    failure.

--*/

PNETLINK_GENERIC_FAMILY
NetpNetlinkGenericLookupFamilyByName (
    PSTR FamilyName
    );

/*++

Routine Description:

    This routine searches the database of registered generic netlink families
    for one with the given name. If successful, the family is returned with an
    added reference which the caller must release.

Arguments:

    FamilyName - Supplies the name of the desired family.

Return Value:

    Returns a pointer to the generic netlink family on success or NULL on
    failure.

--*/

VOID
NetpNetlinkGenericFamilyAddReference (
    PNETLINK_GENERIC_FAMILY Family
    );

/*++

Routine Description:

    This routine increments the reference count of a generic netlink family.

Arguments:

    Family - Supplies a pointer to a generic netlink family.

Return Value:

    None.

--*/

VOID
NetpNetlinkGenericFamilyReleaseReference (
    PNETLINK_GENERIC_FAMILY Family
    );

/*++

Routine Description:

    This routine decrements the reference count of a generic netlink family,
    releasing all of its resources if the reference count drops to zero.

Arguments:

    Family - Supplies a pointer to a generic netlink family.

Return Value:

    None.

--*/

